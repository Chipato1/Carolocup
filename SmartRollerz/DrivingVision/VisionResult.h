#pragma once
enum VisionError {
	SUCCESS, ERROR
};

struct VisionResult
{
	double rho;
	double dy;
	VisionError error;
};


