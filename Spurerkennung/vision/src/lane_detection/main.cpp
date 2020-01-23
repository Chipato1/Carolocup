#include <vision/lane_detection/PointLaneDetector.hpp>

#include <iostream>
#include <map>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <chrono>

std::map<std::string, std::string> readConfigFile() {
	std::ifstream infile("/home/xavier/config/config.cfg");
	std::map<std::string, std::string> my_map;
	if (infile.fail()) {
		std::cerr << "Error: Could not load config file. Reason: " << strerror(errno) << std::endl;
		std::cerr << "Program exit" << std::endl;
		exit(0);
		return my_map;
	}

	std::string line;
	while (std::getline(infile, line)) {
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '=')) {
			std::string value;
			if (std::getline(is_line, value)) {
				std::map<std::string, std::string>::iterator it = my_map.begin();
				my_map.insert(it, std::pair<std::string, std::string>(key, value));
			}
		}
	}
	return my_map;
}

PointLaneDetector* detector;
ros::Publisher visionResultPublisher;
image_transport::Publisher  ipmPublisher;
image_transport::Publisher  thresholdPublisher;
image_transport::Publisher  edgePublisher;
image_transport::Publisher  debugImagePublisher;


void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	auto timeStart = std::chrono::high_resolution_clock::now();
	cv::Mat image = cv_bridge::toCvShare(msg, "mono8")->image;

	detector->calculateFrame(image);
	
	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
	std::cout <<"Dauer Gesamt: " << duration << std::endl;

	sensor_msgs::ImagePtr ipmMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", detector->ipm).toImageMsg();
	sensor_msgs::ImagePtr thresholdMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", detector->threshold).toImageMsg();
	sensor_msgs::ImagePtr edgeMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", detector->edge).toImageMsg();
	sensor_msgs::ImagePtr debugMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", detector->debugImage).toImageMsg();



	//visionResultPublisher.publish(detector->vRes);
	ipmPublisher.publish(ipmMsg);
	thresholdPublisher.publish(thresholdMsg);
	edgePublisher.publish(edgeMsg);
	debugImagePublisher.publish(debugMsg);
	ros::spinOnce();
}

int main(int argc, char** argv) {
	std::cout << "Launching ROS Lane Detection node..." << std::endl;
	std::cout << "Initializing ROS features with parameters: " << std::endl;
	std::cout << "argc: " << argc << "; Node name: vision_lanedetectionnode" << std::endl;
	ros::init(argc, argv, "vision_lanedetectionnode");
	std::cout << "Success!" << std::endl;
	std::cout << "Trying to load config file config.cfg" << std::endl;
	//Config Datei lesen und DrivingVision-Klasse erstellen
	std::map<std::string, std::string> config = readConfigFile();
	std::cout << "Success!" << std::endl;
	detector = new PointLaneDetector(config);
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	//
	image_transport::Subscriber sub = it.subscribe(config["cam_im_topic_name"] , 1, imageCallback);
	
	//visionResultPublisher = nh.advertise<VisionResult>(config["vision_result_topic_name"], 5);
	
	ipmPublisher = it.advertise(config["ipm_result_topic_name"], 1);
	thresholdPublisher = it.advertise(config["threshold_topic_name"], 1);
	edgePublisher = it.advertise(config["edge_topic_name"], 1);
	debugImagePublisher = it.advertise(config["debug_image_topic_name"], 1);

	ros::spin();
	return 0;
}
