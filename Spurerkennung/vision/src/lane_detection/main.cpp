#include <vision/lane_detection/PointLaneDetector.hpp>

#include <iostream>
#include <map>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

std::map<std::string, std::string> readConfigFile() {
	std::ifstream infile("config.cfg");
	std::string line;
	std::map<std::string, std::string> my_map;
	while(std::getline(infile, line)) {
	  	std::istringstream is_line(line);
	  	std::string key;
	  	if( std::getline(is_line, key, '=') ) {
	  	  	std::string value;
	  	  	if( std::getline(is_line, value) ) {
	  	    	map.insert(key, value);
			}
	  	}
	}
	return map;
}

PointLaneDetector detector;

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	cv::Mat image = cv_bridge::toCvShare(msg, "bgr8")->image;
	detector.calculateFrame(image);
}

int main() {
	//Config Datei lesen und DrivingVision-Klasse erstellen
	std::map<std::string, std::string> config = readConfigFile();
	detector = PointLaneDetector(config);

	//ROS Setup
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe(config["edge_image_topic_name"] , 1, imageCallback);
	ros::spin();
	return 0;
}
