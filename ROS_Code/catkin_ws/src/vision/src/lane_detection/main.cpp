/*******************************************************************************
*
* FILENAME: main.cpp
*
* DESCRIPTION: Main entry point for ROS vision lane detection node.
*
* CREATED: 20.02.2020
* AUTHOR: Maximilian Rosnauer
*
* CHANGES:
*  21.02.2020 - Maximilian Rosnauer: Changes for coding guidelines
*  01.01.2020 - Maximilian Rosnauer: File created
*
* Copyright DHBW Smart Rollerz Stuttgart 2019 - 2020. All rights reserved
*
*******************************************************************************/

#include <cv_bridge/cv_bridge.h>
#include <fstream>
#include <image_transport/image_transport.h>
#include <map>
#include <ros/ros.h>
#include <string>
#include <thread>
#include <vision/lane_detection/PointLaneDetector.hpp>
#include <vision/lane_detection/ROS_VIS_LaneDetectionConfig.hpp>
#include <vision/VisionResultMsg.h>
#include <vision/HoughPoints.h>
#include <vision/HoughPointsArray.h>
#include <vision/lane_detection/pinhole_camera_model.h>


ROS_VIS_LaneDetectionConfig* config;
PointLaneDetector *ROS_VIS_detector;
ros::Publisher ROS_VIS_publisher;
ros::Publisher ROS_VIS_houghPublisher;
image_transport::Publisher ROS_VIS_undistortPublisher;
image_transport::Publisher ROS_VIS_ipmPublisher;
image_transport::Publisher ROS_VIS_thresholdImagePublisher;
image_transport::Publisher ROS_VIS_edgePublisher;
image_transport::Publisher ROS_VIS_debugImagePublisher;

sensor_msgs::ImagePtr undistortMsg;
sensor_msgs::ImagePtr ipmMsg;
sensor_msgs::ImagePtr thresholdMsg;
sensor_msgs::ImagePtr edgeMsg;
sensor_msgs::ImagePtr debugMsg;
vision::HoughPointsArray houghMsg;

const std::string ROS_VIS_LANEDETECTIONNODE_NAME = "vision_lanedetectionnode";

bool firstImage = false;

/* 
 * Reads a configuration
 * from a config file
 */
std::map<std::string, std::string> ROS_VIS_readConfigFile()
{
	std::ifstream infile("/home/xavier/config/config.cfg");
	std::map<std::string, std::string> my_map;
	if (infile.fail())
	{
		ROS_WARN("Could not load config file. Reason: %s", strerror(errno));
		return my_map;
	}

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '='))
		{
			std::string value;
			if (std::getline(is_line, value))
			{
				std::map<std::string, std::string>::iterator it = my_map.begin();
				my_map.insert(it, std::pair<std::string, std::string>(key, value));
			}
		}
	}
	ROS_INFO("Successfully read and parsed the config file!");
	return my_map;
}



vision::VisionResultMsg copyToMsg(VisionResult source)
{
	vision::VisionResultMsg result;

	std::copy(std::begin(source.leftLane1), std::end(source.leftLane1), std::begin(result.leftLane1));
	std::copy(std::begin(source.middleLane1), std::end(source.middleLane1), std::begin(result.middleLane1));
	std::copy(std::begin(source.rightLane1), std::end(source.rightLane1), std::begin(result.rightLane1));
	std::copy(std::begin(source.leftLane2), std::end(source.leftLane2), std::begin(result.leftLane2));
	std::copy(std::begin(source.middleLane2), std::end(source.middleLane2), std::begin(result.middleLane2));
	std::copy(std::begin(source.rightLane2), std::end(source.rightLane2), std::begin(result.rightLane2));

	result.clothoideCutDistanceL_mm = source.clothoideCutDistanceL_mm;
	result.clothoideCutDistanceM_mm = source.clothoideCutDistanceM_mm;
	result.clothoideCutDistanceR_mm = source.clothoideCutDistanceR_mm;

	result.foundLL = source.foundLL;
	result.foundML = source.foundML;
	result.foundRL = source.foundRL;

	result.solvedLL1 = source.solvedLL1;
	result.solvedML1 = source.solvedML1;
	result.solvedRL1 = source.solvedRL1;

	result.solvedLL2 = source.solvedLL2;
	result.solvedML2 = source.solvedML2;
	result.solvedRL2 = source.solvedRL2;

	result.oppositeLane = source.oppositeLane;
	return result;
}



void publishHough() {
	while (ros::ok()) {
		std::unique_lock<std::mutex> lk(ROS_VIS_detector->houghMutex);
		ROS_VIS_detector->condition.wait(lk);
		ROS_VIS_detector->houghZumutung.lock();
		std::vector<cv::Vec4i> houghPointsResult;
		if (!ROS_VIS_detector->houghLinesGPU.empty()){
			houghPointsResult.resize(ROS_VIS_detector->houghLinesGPU.cols);
			cv::Mat test;
			ROS_VIS_detector->houghLinesGPU.download(test);
			
			
			ROS_VIS_detector->houghLinesCPU = cv::Mat(1, ROS_VIS_detector->houghLinesGPU.cols, CV_32SC4, &houghPointsResult[0]);
			ROS_VIS_detector->houghLinesGPU.download(ROS_VIS_detector->houghLinesCPU);

			cv::Vec4i l;
			vision::HoughPointsArray msg;
			vision::HoughPoints houghData;
			
			for (size_t i = 0; i < houghPointsResult.size(); i++) {
				//std::cout << i << ":" << houghPointsResult[i] << std::endl;
				l = houghPointsResult[i];
				houghData.x1 = l[0]; 
				houghData.y1 = l[1]; 
				houghData.x2 = l[2];
				houghData.y2 = l[3];
				msg.points.push_back(houghData);	
			}

			 
			ROS_VIS_houghPublisher.publish(msg);
		}
		
		ROS_VIS_detector->houghZumutung.unlock();
	}
}


void imageCallback(const sensor_msgs::ImageConstPtr &msg,
				   const sensor_msgs::CameraInfoConstPtr &info_msg) {
	// Verify camera is actually calibrated
	if (!firstImage)
	{
		std::cout << "Receiving images from camera" << std::endl;

		if (info_msg->K[0] == 0.0)
		{
			std::cerr << "Camera not calibrated" << std::endl;
			return;
		}

		// If zero distortion, just pass the message along
		bool zero_distortion = true;
		for (size_t i = 0; i < info_msg->D.size(); ++i)
		{
			if (info_msg->D[i] != 0.0)
			{
				zero_distortion = false;
				break;
			}
		}
		image_geometry::PinholeCameraModel model_;
		model_.fromCameraInfo(info_msg);
		
		config.->map1GPU = model_.full_map1GPU;
		config.->map2GPU = model_.full_map2GPU;
		ROS_VIS_detector.setConfig(config);

		firstImage = true;
	}
	
	// Create cv::Mat views onto both buffers
	cv::Mat image = cv_bridge::toCvShare(msg, "mono8")->image;
	writer.write(image);

	ROS_VIS_detector->calculateFrame(image);
	image.release();

	undistortMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", ROS_VIS_detector->undistort).toImageMsg();
	ipmMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", ROS_VIS_detector->ipm).toImageMsg();
	thresholdMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", ROS_VIS_detector->threshold).toImageMsg();
	edgeMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", ROS_VIS_detector->edge).toImageMsg();
	debugMsg = cv_bridge::CvImage(std_msgs::Header(), "rgb8", ROS_VIS_detector->debugImage).toImageMsg();

	ROS_VIS_publisher.publish(copyToMsg(ROS_VIS_detector->vRes));
	ROS_VIS_houghPublisher.publish(houghMsg);
	ROS_VIS_undistortPublisher.publish(undistortMsg);
	ROS_VIS_ipmPublisher.publish(ipmMsg);
	ROS_VIS_thresholdImagePublisher.publish(thresholdMsg);
	ROS_VIS_edgePublisher.publish(edgeMsg);
	ROS_VIS_debugImagePublisher.publish(debugMsg);
}

int main(int argc, char **argv)
{
	ROS_INFO("Initializing ROS features with parameters: argc %d; Node name: %s", argc, ROS_VIS_LANEDETECTIONNODE_NAME);
	ros::init(argc, argv, ROS_VIS_LANEDETECTIONNODE_NAME);
	ROS_INFO("Successfully initialized this node!");

	ROS_INFO("Trying to load config file config.cfg... ");
	std::map<std::string, std::string> configObj = ROS_VIS_readConfigFile();
	config = new ROS_VIS_LaneDetectionConfig(configObj);
	
	ROS_INFO("Creating the lane detector object... ";
	ROS_VIS_detector = new PointLaneDetector(config);
	ROS_INFO("Successfully created the lane detector object!");

	ROS_INFO("Subscribing and publishing topics... ");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::CameraSubscriber sub = it.subscribeCamera(config["cam_im_topic_name"], 1, imageCallback);

	ROS_VIS_publisher 				= nh.advertise<vision::VisionResultMsg>(config["vision_result_topic_name"], 1);
	ROS_VIS_houghPublisher 			= nh.advertise<vision::HoughPointsArray>("HoughResult", 1);
	ROS_VIS_undistortPublisher 		= it.advertise(config["undistort_result_topic_name"], 1);
	ROS_VIS_ipmPublisher 			= it.advertise(config["ipm_result_topic_name"], 1);
	ROS_VIS_thresholdImagePublisher = it.advertise(config["threshold_topic_name"], 1);
	ROS_VIS_edgePublisher 			= it.advertise(config["edge_topic_name"], 1);
	ROS_VIS_debugImagePublisher 	= it.advertise(config["debug_image_topic_name"], 1);

	std::thread t1(publishHough);
	ROS_INFO("Successfully initialized the subscribers and publishers");
	ROS_INFO("Lane detection node launched!");

	ros::Rate rate(60.);
	while (ros::ok())
	{
		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}
