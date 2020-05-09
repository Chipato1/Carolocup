#include <ros/ros.h>
#include <iostream>
#include <math.h>

// Messages
#include <sensor_msgs/PointCloud2.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float32MultiArray.h>

// Point cloud library
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/conversions.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/extract_clusters.h>

// Filter
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/crop_box.h>
#include <pcl/filters/voxel_grid.h>

using namespace std;

string frame_id;

// Publisher
ros::Publisher pub_cropbox;
ros::Publisher pub_voxelgrid;
ros::Publisher pub_clustered;
ros::Publisher pub_centroid;
ros::Publisher pub_dist_angl;
ros::Publisher pub_centroid_marker;
ros::Publisher pub_text_marker;
ros::Publisher pub_cropbox_frame;

void callback(const sensor_msgs::PointCloud2ConstPtr& input){
  
  // Container for original and filtered data
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_cropbox (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_voxelgrid (new pcl::PointCloud<pcl::PointXYZ>);

  // Convert to PCL data type
  pcl::PCLPointCloud2* pcl_cloud = new pcl::PCLPointCloud2; 
  pcl::PCLPointCloud2ConstPtr cloudPtr(pcl_cloud);
  pcl_conversions::toPCL(*input, *pcl_cloud);

  // Convert to PointXYZ data type
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromPCLPointCloud2(*pcl_cloud, *cloud);

//**********CropBox*Filter*************************************************
  
  vector<float> boxMin {-1.5, -0.5, 0.0};
  vector<float> boxMax {0, 0.5, 0.0, 1.0};

  pcl::CropBox<pcl::PointXYZ> boxFilter;
  boxFilter.setInputCloud (cloud);
  boxFilter.setMin (Eigen::Vector4f(boxMin[0], boxMin[1], boxMin[2], 1.0));
  boxFilter.setMax (Eigen::Vector4f(boxMax[0], boxMax[1], boxMax[2], 1.0));
  boxFilter.filter (*cloud_filtered_cropbox);

  //ROS_INFO("PointCloud after CropBox filtering has: %d data points", cloud_filtered_cropbox->points.size ());  

  // Convert to PCL data type
  pcl::PCLPointCloud2* pcl_cropbox = new pcl::PCLPointCloud2; 
  pcl::PCLPointCloud2ConstPtr cloudPtr_cropbox(pcl_cropbox);
  pcl::toPCLPointCloud2(*cloud_filtered_cropbox, *pcl_cropbox);

  // Convert to sensor_msgs::PointCloud2 data type
  sensor_msgs::PointCloud2 cropbox;
  pcl_conversions::fromPCL(*pcl_cropbox, cropbox);

  // Publish cloud
  cropbox.header.stamp = ros::Time::now();
  cropbox.header.frame_id = frame_id;
  pub_cropbox.publish(cropbox);

//**********VoxelGrid*Filter***********************************************

  pcl::VoxelGrid<pcl::PointXYZ> vg;
  vg.setInputCloud (cloud_filtered_cropbox);
  vg.setLeafSize (0.01f, 0.01f, 0.01f);
  vg.filter (*cloud_filtered_voxelgrid);

  //ROS_INFO("PointCloud after VoxelGrid filtering has: %d data points", cloud_filtered_voxelgrid->points.size ());

  // Convert to PCL data type
  pcl::PCLPointCloud2* pcl_voxelgrid = new pcl::PCLPointCloud2; 
  pcl::PCLPointCloud2ConstPtr cloudPtr_voxelgrid(pcl_voxelgrid);
  pcl::toPCLPointCloud2(*cloud_filtered_voxelgrid, *pcl_voxelgrid);

  // Convert to sensor_msgs::PointCloud2 data type
  sensor_msgs::PointCloud2 voxelgrid;
  pcl_conversions::fromPCL(*pcl_voxelgrid, voxelgrid);

  // Publish cloud
  voxelgrid.header.stamp = ros::Time::now();
  voxelgrid.header.frame_id = frame_id;
  pub_voxelgrid.publish(voxelgrid);

//**********Marker*objects*************************************************

  // Create centroid marker object
  visualization_msgs::Marker centroids;
  centroids.header.frame_id = frame_id;
  centroids.type = visualization_msgs::Marker::POINTS;
  centroids.scale.x = 0.05;
  centroids.scale.y = 0.05;
  centroids.color.r = 1.0f;
  centroids.color.a = 1.0;

  // Create distance and angle marker object
  visualization_msgs::Marker text;
  text.header.frame_id = frame_id;
  text.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  text.scale.z = 0.1;
  text.color.r = 1.0;
  text.color.g = 1.0;
  text.color.b = 1.0;
  text.color.a = 1.0;

//**********Clustering*****************************************************

  cloud_filtered = cloud_filtered_voxelgrid;

  // Creating the KdTree object for the search method of the extraction
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
  tree->setInputCloud (cloud_filtered);

  // Euclidean cluster extraction
  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
  ec.setClusterTolerance (0.02); // 2cm
  ec.setMinClusterSize (10);
  ec.setMaxClusterSize (cloud_filtered->points.size());
  ec.setSearchMethod (tree);
  ec.setInputCloud (cloud_filtered);
  ec.extract (cluster_indices);

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);
  float centroid_X, centroid_Y, centroid_Z;
  for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); it++)
  {
    int index = it - cluster_indices.begin();
    int count = 0;
    centroid_X = centroid_Y = centroid_Z = 0;

    for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); ++pit) {
      cloud_cluster->points.push_back (cloud_filtered->points[*pit]);
      centroid_X += cloud_filtered->points[*pit].x;
      centroid_Y += cloud_filtered->points[*pit].y;
      count ++;
    }
    cloud_cluster->width = cloud_cluster->points.size();
    cloud_cluster->height = 1;
    cloud_cluster->is_dense = true;

    //ROS_INFO("PointCloud after clustering has: %d data points", cloud_cluster->points.size());
  
    // Convert to PCL data type
    pcl::PCLPointCloud2* pcl_cluster = new pcl::PCLPointCloud2; 
    pcl::PCLPointCloud2ConstPtr cloudPtr_clustered(pcl_cluster);
    pcl::toPCLPointCloud2(*cloud_cluster, *pcl_cluster);

    // Convert to sensor_msgs::PointCloud2 data type
    sensor_msgs::PointCloud2 cluster;
    pcl_conversions::fromPCL(*pcl_cluster, cluster);

    // Publish clustered cloud
    cluster.header.frame_id = frame_id;
    cluster.header.stamp = ros::Time::now();
    pub_clustered.publish(cluster);

//**********Centroids*Distance*Angle***************************************

    // Publish centroids
    geometry_msgs::Point point;
    if (count) {
        point.x = centroid_X / count;
        point.y = centroid_Y / count;
        point.z = centroid_Z / count; 
    }
    pub_centroid.publish(point);

    // Calculate distance
    float distance = sqrt(point.x * point.x + point.y * point.y);

    // Calculate angle
    // Rotate to fit RPLIDAR A2 coordinate system
    float coord_x =   point.y;
    float coord_y = - point.x;
    float angle = atan2(coord_x, coord_y);
    angle *= 180 / M_PI; // Convert from Rad to Deg
    
    // Publish distance and angle
    std_msgs::Float32MultiArray dist_angl;
    dist_angl.data.clear();
    dist_angl.data.push_back(distance);
    dist_angl.data.push_back(angle);
    pub_dist_angl.publish(dist_angl);

    ROS_INFO("Object [%i] distance: %0.1f angle %0.1f", index, distance, angle);

//**********Markers********************************************************

    // Publish marker of centroid of each cluster to visualize in RVIZ
    if (pub_centroid_marker.getNumSubscribers() > 0) {
        // Destroy old centroid markers
        centroids.action = visualization_msgs::Marker::DELETEALL;
        pub_centroid_marker.publish(centroids);
        // Publish new centroid markers
        centroids.action = visualization_msgs::Marker::ADD;
        centroids.header.stamp = ros::Time::now();
        centroids.id = index;
        centroids.points.push_back(point);   
        pub_centroid_marker.publish(centroids);
    }
    
    // Publish marker of distance and angle of each cluster to visualize in RVIZ
    if (pub_text_marker.getNumSubscribers() > 0) {
        
	// Destroy old text markers
        //text.action = visualization_msgs::Marker::DELETEALL;
        //pub_text_marker.publish(text);
        // Publish new text markers
        text.action = visualization_msgs::Marker::ADD;
        text.header.stamp = ros::Time::now();
        text.id = index;
        text.pose.position.x = point.x-0.2;
        text.pose.position.y = point.y;
        text.pose.position.z = point.z;
        std::stringstream ss;
        ss.precision(2);
        ss << fixed << "distance: " << distance << "\nangle: " << angle;
        std::string s = ss.str();
        text.text = s;
        pub_text_marker.publish(text);
    }
  }
  // Publish marker of cropbox frame to visualize in RVIZ
  visualization_msgs::Marker box;
  box.header.frame_id = frame_id;
  box.type = visualization_msgs::Marker::LINE_LIST;
  box.scale.x = 0.01;
  box.color.g = 1.0;
  box.color.a = 1.0;
  box.pose.orientation.w = 1.0;
  box.action = visualization_msgs::Marker::ADD;
  box.header.stamp = ros::Time::now();
  geometry_msgs::Point p;
  p.x = boxMin[0];
  p.y = boxMin[1];
  p.z = boxMin[2];
  box.points.push_back(p);
  p.x = boxMin[0];
  p.y = boxMax[1];
  p.z = boxMin[2];
  box.points.push_back(p);
  box.points.push_back(p);
  p.x = boxMax[0];
  p.y = boxMax[1];
  p.z = boxMin[2];
  box.points.push_back(p);
  box.points.push_back(p);
  p.x = boxMax[0];
  p.y = boxMin[1];
  p.z = boxMin[2];
  box.points.push_back(p);
  box.points.push_back(p);
  p.x = boxMin[0];
  p.y = boxMin[1];
  p.z = boxMin[2];
  box.points.push_back(p);
  pub_cropbox_frame.publish(box);
}

//**********MAIN***********************************************************

int main (int argc, char** argv)
{
  ros::init(argc, argv, "object_detection");
  ros::NodeHandle nh;
  ros::Rate r(30);

//**********Publisher******************************************************
  pub_cropbox = nh.advertise<sensor_msgs::PointCloud2>("pointcloud_filtered_cropbox",1);  
  pub_voxelgrid = nh.advertise<sensor_msgs::PointCloud2>("pointcloud_filtered_voxelgrid",1);  
  pub_clustered = nh.advertise<sensor_msgs::PointCloud2>("pointcloud_clustered",1);  
  pub_centroid = nh.advertise<geometry_msgs::Point>("centroid_point",1);
  pub_dist_angl = nh.advertise<std_msgs::Float32MultiArray>("distance_angle",1);
  pub_centroid_marker = nh.advertise<visualization_msgs::Marker>("centroid_marker",1);
  pub_text_marker = nh.advertise<visualization_msgs::Marker>("distance_angle_marker",1);
  pub_cropbox_frame = nh.advertise<visualization_msgs::Marker>("cropbox_frame_marker",1);

//**********Subscriber*****************************************************
  ros::Subscriber sub_pointcloud = nh.subscribe<sensor_msgs::PointCloud2>("pointcloud", 1, callback);

//**********Parameter******************************************************
  ros::NodeHandle nh_private("~");
  nh_private.param<std::string>("frame_id", frame_id, "laser");

  ros::spin();
  r.sleep();

  return (0);
}

