#include "image_geometry/pinhole_camera_model.h"
#include <sensor_msgs/distortion_models.h>
#include <opencv2/core/cuda.hpp>
#ifdef BOOST_SHARED_PTR_HPP_INCLUDED
#include <boost/make_shared.hpp>
#endif

namespace image_geometry
{

enum DistortionState
{
  NONE,
  CALIBRATED,
  UNKNOWN
};

PinholeCameraModel::PinholeCameraModel()
{
}

PinholeCameraModel::PinholeCameraModel(const PinholeCameraModel &other)
{
  if (other.initialized())
    fromCameraInfo(other.cam_info_);
}

// For uint32_t, string, bool...
template <typename T>
bool update(const T &new_val, T &my_val)
{
  if (my_val == new_val)
    return false;
  my_val = new_val;
  return true;
}

// For std::vector
template <typename MatT>
bool updateMat(const MatT &new_mat, MatT &my_mat, cv::Mat_<double> &cv_mat, int rows, int cols)
{
  if ((my_mat == new_mat) && (my_mat.size() == cv_mat.rows * cv_mat.cols))
    return false;
  my_mat = new_mat;
  // D may be empty if camera is uncalibrated or distortion model is non-standard
  cv_mat = (my_mat.size() == 0) ? cv::Mat_<double>() : cv::Mat_<double>(rows, cols, &my_mat[0]);
  return true;
}

template <typename MatT, typename MatU>
bool updateMat(const MatT &new_mat, MatT &my_mat, MatU &cv_mat)
{
  if ((my_mat == new_mat) && (my_mat.size() == cv_mat.rows * cv_mat.cols))
    return false;
  my_mat = new_mat;
  // D may be empty if camera is uncalibrated or distortion model is non-standard
  cv_mat = MatU(&my_mat[0]);
  return true;
}

bool PinholeCameraModel::fromCameraInfo(const sensor_msgs::CameraInfo &msg)
{
  // Binning = 0 is considered the same as binning = 1 (no binning).
  uint32_t binning_x = msg.binning_x ? msg.binning_x : 1;
  uint32_t binning_y = msg.binning_y ? msg.binning_y : 1;

  // ROI all zeros is considered the same as full resolution.
  sensor_msgs::RegionOfInterest roi = msg.roi;
  if (roi.x_offset == 0 && roi.y_offset == 0 && roi.width == 0 && roi.height == 0)
  {
    roi.width = msg.width;
    roi.height = msg.height;
  }

  // Update time stamp (and frame_id if that changes for some reason)
  cam_info_.header = msg.header;

  // Update any parameters that have changed. The full rectification maps are
  // invalidated by any change in the calibration parameters OR binning.

  update(msg.height, cam_info_.height);
  update(msg.width, cam_info_.width);
  update(msg.distortion_model, cam_info_.distortion_model);
  updateMat(msg.D, cam_info_.D, D_, 1, msg.D.size());
  updateMat(msg.K, cam_info_.K, K_full_);
  updateMat(msg.R, cam_info_.R, R_);
  updateMat(msg.P, cam_info_.P, P_full_);
  update(binning_x, cam_info_.binning_x);
  update(binning_y, cam_info_.binning_y);

  update(roi.x_offset, cam_info_.roi.x_offset);
  update(roi.y_offset, cam_info_.roi.y_offset);
  update(roi.height, cam_info_.roi.height);
  update(roi.width, cam_info_.roi.width);
  update(roi.do_rectify, cam_info_.roi.do_rectify);
  // As is the rectified ROI

  // Figure out how to handle the distortion
  if (cam_info_.distortion_model == sensor_msgs::distortion_models::PLUMB_BOB ||
      cam_info_.distortion_model == sensor_msgs::distortion_models::RATIONAL_POLYNOMIAL)
  {
    // If any distortion coefficient is non-zero, then need to apply the distortion
    distortion_state = NONE;
    for (size_t i = 0; i < cam_info_.D.size(); ++i)
    {
      if (cam_info_.D[i] != 0)
      {
        distortion_state = CALIBRATED;
        break;
      }
    }
  }
  else
    distortion_state = UNKNOWN;

  // If necessary, create new K_ and P_ adjusted for binning and ROI
  /// @todo Calculate and use rectified ROI
  bool adjust_binning = (binning_x > 1) || (binning_y > 1);
  bool adjust_roi = (roi.x_offset != 0) || (roi.y_offset != 0);

  if (!adjust_binning && !adjust_roi)
  {
    K_ = K_full_;
    P_ = P_full_;
  }
  else
  {
    K_ = K_full_;
    P_ = P_full_;

    // ROI is in full image coordinates, so change it first
    if (adjust_roi)
    {
      // Move principal point by the offset
      /// @todo Adjust P by rectified ROI instead
      K_(0, 2) -= roi.x_offset;
      K_(1, 2) -= roi.y_offset;
      P_(0, 2) -= roi.x_offset;
      P_(1, 2) -= roi.y_offset;
    }

    if (binning_x > 1)
    {
      double scale_x = 1.0 / binning_x;
      K_(0, 0) *= scale_x;
      K_(0, 2) *= scale_x;
      P_(0, 0) *= scale_x;
      P_(0, 2) *= scale_x;
      P_(0, 3) *= scale_x;
    }
    if (binning_y > 1)
    {
      double scale_y = 1.0 / binning_y;
      K_(1, 1) *= scale_y;
      K_(1, 2) *= scale_y;
      P_(1, 1) *= scale_y;
      P_(1, 2) *= scale_y;
      P_(1, 3) *= scale_y;
    }
  }

  return true;
}

bool PinholeCameraModel::fromCameraInfo(const sensor_msgs::CameraInfoConstPtr &msg)
{
  return fromCameraInfo(*msg);
}


void PinholeCameraModel::initRectificationMaps() const
{

  cv::Size binned_resolution = fullResolution();
  binned_resolution.width /= binningX();
  binned_resolution.height /= binningY();

  cv::Matx33d K_binned;
  cv::Matx34d P_binned;
  if (binningX() == 1 && binningY() == 1)
  {
    K_binned = K_full_;
    P_binned = P_full_;
  }
  else
  {
    K_binned = K_full_;
    P_binned = P_full_;
    if (binningX() > 1)
    {
      double scale_x = 1.0 / binningX();
      K_binned(0, 0) *= scale_x;
      K_binned(0, 2) *= scale_x;
      P_binned(0, 0) *= scale_x;
      P_binned(0, 2) *= scale_x;
      P_binned(0, 3) *= scale_x;
    }
    if (binningY() > 1)
    {
      double scale_y = 1.0 / binningY();
      K_binned(1, 1) *= scale_y;
      K_binned(1, 2) *= scale_y;
      P_binned(1, 1) *= scale_y;
      P_binned(1, 2) *= scale_y;
      P_binned(1, 3) *= scale_y;
    }
  }

  // Note: m1type=CV_16SC2 to use fast fixed-point maps (see cv::remap)
  cv::initUndistortRectifyMap(K_binned, D_, R_, P_binned, binned_resolution,
                              CV_16SC2, full_map1, full_map2);
  full_map1GPU.upload(full_map1);
  full_map2GPU.upload(full_map2);
}

} //namespace image_geometry
