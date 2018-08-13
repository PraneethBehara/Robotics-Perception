#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "pcd_handler.h"

using namespace std;
using namespace pcl;

ros::Publisher pub_allobjects;

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& pc2_msg)
{
  if (pc2_msg->data.size()) {

    // Convert ROS msg to PCL Point Cloud 
    PointCloud<PointXYZRGB>::Ptr in_cloud(new PointCloud<PointXYZRGB>);
    fromROSMsg(*pc2_msg, *in_cloud);

    PCDHandler* segobj (new PCDHandler);

    // Downsampling cloud
    PointCloud<PointXYZRGB>::Ptr downsampledcloud(new PointCloud<PointXYZRGB>);
    downsampledcloud = segobj->DownsamplePCD(in_cloud);

    // Applying Passthrough filter
    PointCloud<PointXYZRGB>::Ptr passthroughcloud(new PointCloud<PointXYZRGB>);
    passthroughcloud = segobj->PassThroughFilter(downsampledcloud);

    // Debug {begin}
    // segobj-> displayCloud(in_cloud);  
    // segobj-> displayCloud(downsampledcloud);
    // segobj-> displayCloud(passthroughcloud);
    // Debug {end}

    // Applying RANSAC Plane Segmentation

    // cerr << "PointCloud passthroughsize: " << passthroughcloud->width * passthroughcloud->height 
    //       << " data points (" << getFieldsList (*passthroughcloud) << ")." << endl;
    
    vector<PointCloud<PointXYZRGB>::Ptr> ptrclouds;
    ptrclouds = segobj-> RANSAC(passthroughcloud);  
    
    // cerr << "PointCloud ransac size: " << ptrclouds[0]->width * ptrclouds[0]->height 
    //       << " data points (" << getFieldsList (*ptrclouds[0]) << ")." << endl;

    // cerr << "PointCloud ransac size: " << ptrclouds[1]->width * ptrclouds[1]->height 
    //       << " data points (" << getFieldsList (*ptrclouds[1]) << ")." << endl;

    // Convert to ROS msg
    sensor_msgs::PointCloud2 tabletop_objects;
    toROSMsg(*ptrclouds[1], tabletop_objects);

    pub_allobjects.publish(tabletop_objects);
  
    // Delete pointer
    delete segobj;
  }
}

int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "segment_helper");

  ros::NodeHandle nh;

  // Create a ROS publisher for the output point clouds
  pub_allobjects = nh.advertise<sensor_msgs::PointCloud2> ("/tabletop_objects", 1);
  
  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("/sensor_stick/point_cloud", 1, cloud_cb);

  ros::spin ();
}