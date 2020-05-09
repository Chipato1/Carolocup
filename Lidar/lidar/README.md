
#**LiDAR ROS package**
============================================================================

- Starts the RPLIDAR A2
- Produces laserscans
- Transforms them into a pointcloud
- Filters the pointcloud
- Builds clusters
- Detects the objects

----------------------------------------------------------------------------
Details about RPLIDAR:
- roswiki:	http://wiki.ros.org/rplidar
- website:	http://www.slamtec.com/en/Lidar
- SDK: 		https://github.com/Slamtec/rplidar_sdk
- Tutorial: 	https://github.com/robopeak/rplidar_ros/wiki

Details about PCL:
- roswiki:	http://wiki.ros.org/pcl
- website: 	http://www.pointclouds.org
- repository: 	https://github.com/PointCloudLibrary

----------------------------------------------------------------------------

##**How to build**
- Clone this project to your catkin's workspace src folder
- Running catkin_make to build nodes

##**How to run**
```
- roslaunch lidar object_detection.launch
```
##**Running on VM**
- If you run the code on a VM, then first add write authority for LiDAR device with: 
```
sudo chmod a+rw /dev/ttyUSB0	
```

----------------------------------------------------------------------------

##**Published topics**
- /scan				sensor_msgs/LaserScan		#scan produces from LiDAR

- /pointcloud			sensor_msgs/PointCloud2		#pointcloud transformed from laserscan

- /pointcloud_filtered_cropbox	sensor_msgs/PointCloud2		#pointcloud after cropbox filter

- /pointcloud_filtered_voxelgrid	sensor_msgs/PointCloud2		#pointcloud after voxelgrid filter

- /pointcloud_clustered		sensor_msgs/PointCloud2		#pointcloud of detected clusters

- /centroid_point			geometry_msgs/Point		#point of center of cluster

- /distance_angle			std_msgs/Float32MultiArray	#distance in m and angle in intervall [-180°,180°] of centroids 

- /cropbox_frame_marker		visualization_msgs/Marker	#marker to visualize cropbox frame in RVIZ

- /centroid_marker		visualization_msgs/Marker	#marker to visualize centroids of clusters in RVIZ

- /distance_angle_marker		visualization_msgs/Marker	#marker to visualize text with distance and angle of centroids in RVIZ

Note: to visualize markers in RVIZ change "Fixed Frame" in RVIZ to "laser"

----------------------------------------------------------------------------

**TODO**
- [] define interface (Datatype: position, distance, angle)
  








