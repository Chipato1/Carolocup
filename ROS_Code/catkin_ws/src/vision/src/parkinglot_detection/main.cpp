#include <vision/parkinglot_detection/ParkinglotDetector.hpp>

#include <vison/ParkinglotMsg.h>

#include <iostream>
#include <map>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <chrono>
std::map<std::string, std::string> config;





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

ParkinglotDetector detector;
double distance;
bool parkinglotFound;
ros::Publisher parkinglotPublisher;




void imageCallback(const vision::HoughPointsArray::ConstPtr& msg) {
	cv::Mat image = cv_bridge::toCvShare(msg, "mono8")->image;
	//---------------------    -------CODE HIER EINFÜGEN---------------
	distance = detector.detectParkinglots(msg, config);

	if (distance > -1)
	{
		parkinglotFound = true;
	}
	else
	{
		parkinglotFound = false;
	}

	vision::ParkinglotMsg lotmsg;
	lotmsg.distance = distance;
	lotmsg.parkinglotDetected = parkinglotFound;

	parkinglotPublisher.publish(lotmsg);
}





int main(int argc, char** argv) {
	std::cout << "Launching ROS Lane Detection node..." << std::endl;
	std::cout << "Initializing ROS features with parameters: " << std::endl;
	std::cout << "argc: " << argc << "; Node name: vision_lanedetectionnode" << std::endl;
	ros::init(argc, argv, "vision_lanedetectionnode");
	std::cout << "Success!" << std::endl;
	std::cout << "Trying to load config file config.cfg" << std::endl;
	//Config Datei lesen und DrivingVision-Klasse erstellen
	config = readConfigFile();
	std::cout << "Success!" << std::endl;

	ros::NodeHandle nh;
	//image_transport::ImageTransport it(nh);
	parkinglotPublisher = nh.advertise<vision::ParkinglotMsg>(("Parkinglot", 1);
	ros::Subscriber sub = nh.subscribe("HoughResult" , 1, imageCallback);
	ros::spin();


	
	return 0;
}
