/*
ROS node for point cloud segmentation of tabletop objects
Author : Praneeth Behara
*/

#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/features/normal_3d.h> //required for kdtree
#include "pcd_handler.h"
#include <pcd_object_detection/SegmentedClusters.h>

using namespace std;
using namespace pcl;

class PCDSegmentation {
  public:
  int colors[10][3];

  explicit PCDSegmentation(ros::NodeHandle nh){
    m_nh = nh;
    m_sub = m_nh.subscribe ("/tabletop_objects", 1, &PCDSegmentation::objects_cb, this);
    m_pub_segcloud = m_nh.advertise<sensor_msgs::PointCloud2> ("/segmented_cloud", 1);
    m_pub_clusters = m_nh.advertise<pcd_object_detection::SegmentedClusters> ("/clusters", 1);
    int colors[10][3] = {{255,155,25},{152,255,45},{0,0,255},
                                                {0,255,100},{255,0,0},{25,125,255},
                                                {200,125,255},{155,0,255},{255,255,0},
                                                {0,255,255}};
  }

  private:
  ros::NodeHandle m_nh;
  ros::Publisher m_pub_segcloud;
  ros::Publisher m_pub_clusters;
  ros::Subscriber m_sub;

  void objects_cb(const sensor_msgs::PointCloud2ConstPtr& cloud_msg);
  void publishPointCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, std::string frameID);
}; //end of class definition 

void PCDSegmentation::publishPointCloud(PointCloud<PointXYZRGB>::Ptr pointcloud, string frameID) {
  sensor_msgs::PointCloud2 outcloud;
  toROSMsg(*pointcloud, outcloud);
  outcloud.header.frame_id = frameID;
  m_pub_segcloud.publish(outcloud);
}

void PCDSegmentation::objects_cb(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  ROS_INFO("Received cloud msg");
  // cerr << "PointCloud entry size: " << cloud_msg->width * cloud_msg->height 
  //       << " data points (" << getFieldsList (*cloud_msg) << ")." << endl;

  // Convert ROS msg to PCL Point<XYZRGB> 
  PointCloud<PointXYZRGB>::Ptr in_cloud(new PointCloud<PointXYZRGB>);
  fromROSMsg(*cloud_msg, *in_cloud);

  // Segmentation for table top objects
  // Create Kd-tree data struct for unsegmented point cloud
  search::KdTree<PointXYZRGB>::Ptr tree (new search::KdTree<PointXYZRGB> ());
  tree->setInputCloud(in_cloud);

  // Create empty list of clusters and euclidean cluster extraction object
  vector<PointIndices> cluster_indices; //contains all clusters after extraction 
  EuclideanClusterExtraction<PointXYZRGB> ec;
  ec.setClusterTolerance(0.02); //2cm
  ec.setMinClusterSize(100);
  ec.setMaxClusterSize(25000);
  ec.setSearchMethod(tree);
  ec.setInputCloud(in_cloud);
  ec.extract(cluster_indices);

  cout << "Number of clusters segmented :" << cluster_indices.size() << endl;

  // Declare custom message instance
  pcd_object_detection::SegmentedClusters outclusters;

  // Create new PC with segmented clusters and assign unique colors
  PointCloud<PointXYZRGB>::Ptr clubbedClusters (new PointCloud<PointXYZRGB>);

  int r, g, b;
  int count = 0;
  
  vector<PointIndices>::const_iterator itr;
  for (itr=cluster_indices.begin(); itr!= cluster_indices.end(); ++itr){
    vector<int>::const_iterator pit;

    // Create a cloud to hold the cluster
    PointCloud<PointXYZRGB>::Ptr clusterPtr(new PointCloud<PointXYZRGB>);


    for (pit=itr->indices.begin(); pit!=itr->indices.end(); ++pit) {
      clusterPtr->points.push_back (in_cloud->points[*pit]);
    }

    // get random color for cluster
    uint32_t rgb = (colors[count][0] << 16 | (colors[count][1] << 8) | colors[count][2]);
    
    for (int it=0; it!=clusterPtr->points.size(); ++it)
      clusterPtr->points[it].rgb = *reinterpret_cast<float*>(&rgb);   

    clusterPtr->width = clusterPtr->points.size();
    clusterPtr->height = 1;
    clusterPtr->is_dense = true;
    
    sensor_msgs::PointCloud2 currentmsg;
    toROSMsg(*clusterPtr, currentmsg);

    clubbedClusters->operator+=(*clusterPtr);

    // add cluster to message
    outclusters.clusters.push_back(currentmsg);
    count +=1;
  }

  publishPointCloud(clubbedClusters, cloud_msg->header.frame_id);

  outclusters.header.frame_id = cloud_msg->header.frame_id;
  m_pub_clusters.publish(outclusters);
}

int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "euclidean_clustering");

  ros::NodeHandle nh;

  PCDSegmentation seg_obj(nh);

  while(ros::ok())
    ros::spin ();
}