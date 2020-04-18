#include <vision\lane_detection\ROS_VIS_LaneDetectionConfig.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

ROS_VIS_LaneDetectionConfig::ROS_VIS_LaneDetectionConfig()
{
}

ROS_VIS_LaneDetectionConfig::ROS_VIS_LaneDetectionConfig(std::map<std::string, std::string>& config)
{
	double camera_angle_pitch = config.count("camera_angle_pitch") ? stod(config["camera_angle_pitch"]) : 17.77;
	double camera_angle_roll = config.count("camera_angle_roll") ? stod(config["camera_angle_roll"]) : 0.0;
	double camera_angle_yaw = config.count("camera_angle_yaw") ? stod(config["camera_angle_yaw"]) : 0.0;
	double camera_focallength = config.count("camera_focallength") ? stod(config["camera_focallength"]) : 6.0;
	double camera_height = config.count("camera_height") ? stod(config["camera_height"]) : 250.0;
	double cameraResolutionWidth = config.count("camera_res_wid") ? stod(config["camera_res_wid"]) : 1600;
	double cameraResolutionHeight = config.count("camera_res_hei") ? stod(config["camera_res_hei"]) : 1200;

	this->cameraImageSize = cv::Size(cameraResolutionWidth, cameraResolutionHeight);
	
	this->ipmScaling = config.count("ipm_scaling") ? stod(config["ipm_scaling"]) : 1;
	double ipmSizeX = config.count("ipm_size_x") ? stod(config["ipm_size_x"]) : 1200;
	double ipmSizeY = config.count("ipm_size_y") ? stod(config["ipm_size_y"]) : 2400;
	this->ipmImageSize = cv::Size(ipmSizeX * this->ipmScaling, ipmSizeY * this->ipmScaling);

	double ipm_correction = config.count("ipm_correction") ? stod(config["ipm_correction"]) : 420;

	this->thresholdingMode = config.count("thresh_mode") ? stod(config["thresh_mode"]) : 0;
	this->thresholding = config.count("thres_cut") ? stod(config["thres_cut"]) : 127;
	this->otsuThresholdingRefreshMaximum = config.count("thresh_refresh") ? stod(config["thresh_refresh"]) : 100;
	this->otsuThresholdingRefreshCounter = this->otsuThresholdingRefreshMaximum;
	this->otsuThresholdingCorrectionFactor = config.count("thresh_otsu_correction") ? stod(config["thresh_otsu_correction"]) : 50;

	this->cannyLowThreshold = config.count("canny_low_thresh") ? stod(config["canny_low_thresh"]) : 50;
	this->cannyHighThreshold = config.count("canny_high_thresh") ? stod(config["canny_high_thresh"]) : 80;
	this->cannyApertureSize = config.count("canny_aperture_size") ? stod(config["canny_aperture_size"]) : 3;

	this->LANE_THRES_MIN = config.count("LANE_THRES_MIN") ? stoi(config["LANE_THRES_MIN"]) : 17;
	this->LANE_THRES_MAX = config.count("LANE_THRES_MAX") ? stoi(config["LANE_THRES_MAX"]) : 0;
	this->LL_MIN_X = config.count("LL_MIN_X") ? stoi(config["LL_MIN_X"]) : 250;
	this->LL_MAX_X = config.count("LL_MAX_X") ? stoi(config["LL_MAX_X"]) : 350;
	this->ML_MIN_X = config.count("ML_MIN_X") ? stoi(config["ML_MIN_X"]) : 650;
	this->ML_MAX_X = config.count("ML_MAX_X") ? stoi(config["ML_MAX_X"]) : 850;
	this->RL_MIN_X = config.count("RL_MIN_X") ? stoi(config["RL_MIN_X"]) : 1100;
	this->RL_MAX_X = config.count("RL_MAX_X") ? stoi(config["RL_MAX_X"]) : 1300;

	this->LL_MIN_Y = config.count("LL_MIN_Y") ? stoi(config["LL_MIN_Y"]) : 250;
	this->LL_MAX_Y = config.count("LL_MAX_Y") ? stoi(config["LL_MAX_Y"]) : 350;
	this->ML_MIN_Y = config.count("ML_MIN_Y") ? stoi(config["ML_MIN_Y"]) : 650;
	this->ML_MAX_Y = config.count("ML_MAX_Y") ? stoi(config["ML_MAX_Y"]) : 850;
	this->RL_MIN_Y = config.count("RL_MIN_Y") ? stoi(config["RL_MIN_Y"]) : 1100;
	this->RL_MAX_Y = config.count("RL_MAX_Y") ? stoi(config["RL_MAX_Y"]) : 1300;
	
	this->LANE_THRES_MIN = this->LANE_THRES_MIN * this->ipmScaling;
	this->LANE_THRES_MAX = this->LANE_THRES_MAX * this->ipmScaling;
	this->LL_MIN_X = this->LL_MIN_X * this->ipmScaling;
	this->LL_MAX_X = this->LL_MAX_X * this->ipmScaling;
	this->ML_MIN_X = this->ML_MIN_X * this->ipmScaling;
	this->ML_MAX_X = this->ML_MAX_X * this->ipmScaling;
	this->RL_MIN_X = this->RL_MIN_X * this->ipmScaling;
	this->RL_MAX_X = this->RL_MAX_X * this->ipmScaling;

	this->LL_MIN_Y = this->LL_MIN_Y * this->ipmScaling;
	this->LL_MAX_Y = this->LL_MAX_Y * this->ipmScaling;
	this->ML_MIN_Y = this->ML_MIN_Y * this->ipmScaling;
	this->ML_MAX_Y = this->ML_MAX_Y * this->ipmScaling;
	this->RL_MIN_Y = this->RL_MIN_Y * this->ipmScaling;
	this->RL_MAX_Y = this->RL_MAX_Y * this->ipmScaling;

	this->ignoreXMin = (config.count("ignoreXMin") ? stod(config["ignoreXMin"]) : 0) * ipmScaling;
	this->ignoreXMax = (config.count("ignoreXMax") ? stod(config["ignoreXMax"]) : 0) * ipmScaling;
	this->ignoreYMin = (config.count("ignoreYMin") ? stod(config["ignoreYMin"]) : 0) * ipmScaling;
	this->ignoreYMax = (config.count("ignoreYMax") ? stod(config["ignoreYMax"]) : 0) * ipmScaling;

	double alpha_ = camera_angle_pitch;
	double beta_ = camera_angle_roll;
	double gamma_ = camera_angle_yaw;
	double f_ = camera_focallength;
	double height = camera_height;
	double skew_ = 0;

	double focalLength, dist, alpha, beta, gamma, skew;

	alpha = (alpha_)*M_PI / 180;
	beta = (beta_)*M_PI / 180;
	gamma = (gamma_)*M_PI / 180;
	focalLength = f_;
	dist = height / cos(alpha);
	skew = skew_;

	

	// Projecion matrix 2D -> 3D
	cv::Mat A1 = (cv::Mat_<float>(4, 3) <<
		1, 0, -this->ipmImageSize.width / 2,
		0, 1, -this->ipmImageSize.height + ipm_correction * ipmScaling,
		0, 0, 0,
		0, 0, 1);


	// Rotation matrices Rx, Ry, Rz
	cv::Mat RX = (cv::Mat_<float>(4, 4) <<
		1, 0, 0, 0,
		0, cos(alpha), -sin(alpha), 0,
		0, sin(alpha), cos(alpha), 0,
		0, 0, 0, 1);

	cv::Mat RY = (cv::Mat_<float>(4, 4) <<
		cos(beta), 0, -sin(beta), 0,
		0, 1, 0, 0,
		sin(beta), 0, cos(beta), 0,
		0, 0, 0, 1);

	cv::Mat RZ = (cv::Mat_<float>(4, 4) <<
		cos(gamma), -sin(gamma), 0, 0,
		sin(gamma), cos(gamma), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);


	// R - rotation matrix
	cv::Mat R = RX * RY * RZ;

	// T - translation matrix
	cv::Mat T = (cv::Mat_<float>(4, 4) <<
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, dist * this->ipmScaling,
		0, 0, 0, 1);

	cv::Mat K = (cv::Mat_<float>(3, 4) <<
		1786.874566, 0.000000, 707.636847, 0,
		0.000000, 1796.353286, 559.682000, 0,
		0.000000, 0.000000, 1.000000, 0
		);

	this->ipmTransformationMatrix = K * (T * (R * A1));
}
