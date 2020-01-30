#ifndef IMAGE_GEOMETRY_PINHOLE_CAMERA_MODEL_H
#define IMAGE_GEOMETRY_PINHOLE_CAMERA_MODEL_H

#include <sensor_msgs/CameraInfo.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <stdexcept>
#include <string>

namespace image_geometry {

class Exception : public std::runtime_error
{
public:
  Exception(const std::string& description) : std::runtime_error(description) {}
};

/**
 * \brief Simplifies interpreting images geometrically using the parameters from
 * sensor_msgs/CameraInfo.
 */
class PinholeCameraModel
{
public:

  DistortionState distortion_state;

  cv::Mat_<double> K_binned, P_binned; // Binning applied, but not cropping


  cv::Mat full_map1, full_map2;

  cv::Mat reduced_map1, reduced_map2;

  bool rectified_roi_dirty;
  cv::Rect rectified_roi;

  PinholeCameraModel();

  PinholeCameraModel(const PinholeCameraModel& other);

  /**
   * \brief Set the camera parameters from the sensor_msgs/CameraInfo message.
   */
  bool fromCameraInfo(const sensor_msgs::CameraInfo& msg);

  /**
   * \brief Set the camera parameters from the sensor_msgs/CameraInfo message.
   */
  bool fromCameraInfo(const sensor_msgs::CameraInfoConstPtr& msg);

  /**
   * \brief The resolution at which the camera was calibrated.
   *
   * The maximum resolution at which the camera can be used with the current
   * calibration; normally this is the same as the imager resolution.
   */
  cv::Size fullResolution() const;

  /**
   * \brief Returns the camera info message held internally
   */
  const sensor_msgs::CameraInfo& cameraInfo() const;

  /**
   * \brief Returns the original camera matrix.
   */
  const cv::Matx33d& intrinsicMatrix() const;

  /**
   * \brief Returns the distortion coefficients.
   */
  const cv::Mat_<double>& distortionCoeffs() const;

  /**
   * \brief Returns the rotation matrix.
   */
  const cv::Matx33d& rotationMatrix() const;

  /**
   * \brief Returns the projection matrix.
   */
  const cv::Matx34d& projectionMatrix() const;

  /**
   * \brief Returns the original camera matrix for full resolution.
   */
  const cv::Matx33d& fullIntrinsicMatrix() const;

  /**
   * \brief Returns the projection matrix for full resolution.
   */
  const cv::Matx34d& fullProjectionMatrix() const;

  /**
   * \brief Returns the focal length (pixels) in x direction of the rectified image.
   */
  double fx() const;

  /**
   * \brief Returns the focal length (pixels) in y direction of the rectified image.
   */
  double fy() const;

  /**
   * \brief Returns the x coordinate of the optical center.
   */
  double cx() const;

  /**
   * \brief Returns the y coordinate of the optical center.
   */
  double cy() const;

  /**
   * \brief Returns the x-translation term of the projection matrix.
   */
  double Tx() const;

  /**
   * \brief Returns the y-translation term of the projection matrix.
   */
  double Ty() const;

  /**
   * \brief Returns the number of columns in each bin.
   */
  uint32_t binningX() const;

  /**
   * \brief Returns the number of rows in each bin.
   */
  uint32_t binningY() const;
  
  /**
   * \brief Compute delta u, given Z and delta X in Cartesian space.
   *
   * For given Z, this is the inverse of getDeltaX().
   *
   * \param deltaX Delta X, in Cartesian space
   * \param Z      Z (depth), in Cartesian space
   */
  double getDeltaU(double deltaX, double Z) const;

  /**
   * \brief Compute delta v, given Z and delta Y in Cartesian space.
   *
   * For given Z, this is the inverse of getDeltaY().
   *
   * \param deltaY Delta Y, in Cartesian space
   * \param Z      Z (depth), in Cartesian space
   */
  double getDeltaV(double deltaY, double Z) const;

  /**
   * \brief Compute delta X, given Z in Cartesian space and delta u in pixels.
   *
   * For given Z, this is the inverse of getDeltaU().
   *
   * \param deltaU Delta u, in pixels
   * \param Z      Z (depth), in Cartesian space
   */
  double getDeltaX(double deltaU, double Z) const;

  /**
   * \brief Compute delta Y, given Z in Cartesian space and delta v in pixels.
   *
   * For given Z, this is the inverse of getDeltaV().
   *
   * \param deltaV Delta v, in pixels
   * \param Z      Z (depth), in Cartesian space
   */
  double getDeltaY(double deltaV, double Z) const;



  cv::cuda::GpuMat full_map1GPU = cv::cuda::GpuMat();
  cv::cuda::GpuMat full_map2GPU = cv::cuda::GpuMat();

protected:
  sensor_msgs::CameraInfo cam_info_;
  cv::Mat_<double> D_;           // Unaffected by binning, ROI
  cv::Matx33d R_;           // Unaffected by binning, ROI
  cv::Matx33d K_;           // Describe current image (includes binning, ROI)
  cv::Matx34d P_;           // Describe current image (includes binning, ROI)
  cv::Matx33d K_full_; // Describe full-res image, needed for full maps
  cv::Matx34d P_full_; // Describe full-res image, needed for full maps

  void initRectificationMaps() const;

};


inline const sensor_msgs::CameraInfo& PinholeCameraModel::cameraInfo() const  { return cam_info_; }
inline const cv::Matx33d& PinholeCameraModel::intrinsicMatrix() const  { return K_; }
inline const cv::Mat_<double>& PinholeCameraModel::distortionCoeffs() const { return D_; }
inline const cv::Matx33d& PinholeCameraModel::rotationMatrix() const   { return R_; }
inline const cv::Matx34d& PinholeCameraModel::projectionMatrix() const { return P_; }
inline const cv::Matx33d& PinholeCameraModel::fullIntrinsicMatrix() const  { return K_full_; }
inline const cv::Matx34d& PinholeCameraModel::fullProjectionMatrix() const { return P_full_; }

inline double PinholeCameraModel::fx() const { return P_(0,0); }
inline double PinholeCameraModel::fy() const { return P_(1,1); }
inline double PinholeCameraModel::cx() const { return P_(0,2); }
inline double PinholeCameraModel::cy() const { return P_(1,2); }
inline double PinholeCameraModel::Tx() const { return P_(0,3); }
inline double PinholeCameraModel::Ty() const { return P_(1,3); }

inline uint32_t PinholeCameraModel::binningX() const { return cam_info_.binning_x; }
inline uint32_t PinholeCameraModel::binningY() const { return cam_info_.binning_y; }

inline double PinholeCameraModel::getDeltaU(double deltaX, double Z) const
{
  assert( initialized() );
  return fx() * deltaX / Z;
}

inline double PinholeCameraModel::getDeltaV(double deltaY, double Z) const
{
  assert( initialized() );
  return fy() * deltaY / Z;
}

inline double PinholeCameraModel::getDeltaX(double deltaU, double Z) const
{
  assert( initialized() );
  return Z * deltaU / fx();
}

inline double PinholeCameraModel::getDeltaY(double deltaV, double Z) const
{
  assert( initialized() );
  return Z * deltaV / fy();
}

} //namespace image_geometry

#endif
