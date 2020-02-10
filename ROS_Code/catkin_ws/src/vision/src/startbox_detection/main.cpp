#include <vision/startbox_detection/StartboxDetector.hpp>
#include <vision/SetBool.h>

#include <iostream>
#include <map>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <chrono>

#include <condition_variable>

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

cv::Mat image;
StartboxDetector detector = StartboxDetector();
std::mutex imageMutex;
std::mutex signalingMutex;
std::condition_variable condition;
bool detectQRCode(vision::SetBool::Request  &req, vision::SetBool::Response &res) {
	imageMutex.lock();
	cv::Mat copyImage = image.clone();
	imageMutex.unlock();
	bool status = false;
	ROS_INFO("TEST1");
	vector<decodedObject> decodedObjects;
	for(int i = 0; i < 100; i++) {
		std::unique_lock<std::mutex> lk(signalingMutex);
		condition.wait(lk);
		if(detector.checkQRCodeOpenCV(copyImage)) {
			res.success = true;
			return true;
		}
		ROS_INFO("TEST2");

		detector.checkQRCode(copyImage, decodedObjects);

		if(decodedObjects.size() > 0) {
			res.success = true;
			return true;
		}
		ROS_INFO("TEST3");
	}
	res.success = false;
	return false;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	imageMutex.lock();
	image = cv_bridge::toCvShare(msg, "mono8")->image;
	std::lock_guard<std::mutex> lk(signalingMutex);
	condition.notify_one();
	imageMutex.unlock();
	//---------------CODE HIER EINFÜGEN---------------------
    
}

int main(int argc, char** argv) {
	std::cout << "Launching ROS Lane Detection node..." << std::endl;
	std::cout << "Initializing ROS features with parameters: " << std::endl;
	std::cout << "argc: " << argc << "; Node name: vision_lanedetectionnode" << std::endl;
	ros::init(argc, argv, "vision_startboxdetectionnnode");
	std::cout << "Success!" << std::endl;
	std::cout << "Trying to load config file config.cfg" << std::endl;
	//Config Datei lesen und DrivingVision-Klasse erstellen
	std::map<std::string, std::string> config = readConfigFile();
	std::cout << "Success!" << std::endl;

	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("undistortresultimage" , 1, imageCallback);

	ros::ServiceServer service = nh.advertiseService("qr_detected", detectQRCode);

	ros::spin();
	return 0;
}
