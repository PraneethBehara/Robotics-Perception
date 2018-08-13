#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace pcl;
using namespace std;

class PCDHandler {
    public:
    // methods
    void displayCloud (PointCloud<PointXYZRGB>::Ptr cloud);
    PointCloud<PointXYZRGB>::Ptr PassThroughFilter(PointCloud<PointXYZRGB>::Ptr in_cloud);
    PointCloud<PointXYZRGB>::Ptr DownsamplePCD(PointCloud<PointXYZRGB>::Ptr in_cloud);
    vector<PointCloud<PointXYZRGB>::Ptr> RANSAC(PointCloud<PointXYZRGB>::Ptr in_cloud);
    void SaveCloud(string filename, PointCloud<PointXYZRGB>::Ptr cloud, bool binary);
};

void PCDHandler::displayCloud (PointCloud<PointXYZRGB>::Ptr cloud) {
    visualization::PCLVisualizer viewer ("Cloud Viewer");
    viewer.addPointCloud(cloud, "cloud");
    viewer.spin();
 }

PointCloud<PointXYZRGB>::Ptr PCDHandler::PassThroughFilter(PointCloud<PointXYZRGB>::Ptr in_cloud) {
    PassThrough<PointXYZRGB> pass;
    PointCloud<PointXYZRGB>::Ptr out_cloud (new PointCloud<PointXYZRGB>());

    pass.setInputCloud (in_cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (-0.7,0.77);
    pass.setFilterLimitsNegative (true);
    pass.filter (*out_cloud);

    return out_cloud;
}

PointCloud<PointXYZRGB>::Ptr PCDHandler::DownsamplePCD(PointCloud<PointXYZRGB>::Ptr in_cloud) {
    // Create the filtering object
    PointCloud<PointXYZRGB>::Ptr cloud_filtered (new PointCloud<PointXYZRGB>);
    VoxelGrid<PointXYZRGB> sor;
    sor.setInputCloud (in_cloud);
    sor.setLeafSize (0.005f, 0.005f, 0.005f);
    sor.filter (*cloud_filtered);

    // cerr << "PointCloud before filtering: " << in_cloud->width * in_cloud->height 
    //     << " data points (" << getFieldsList (*in_cloud) << ")." << endl;

    // cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
    //     << " data points (" << getFieldsList (*cloud_filtered) << ")." << endl;

    return cloud_filtered;
}

void PCDHandler::SaveCloud(string filename, PointCloud<PointXYZRGB>::Ptr cloud, bool binary) {
    PCDWriter writer;
    writer.write<PointXYZRGB> (filename, *cloud, binary);
}

// Returns a pointer to array of clouds (seg and unseg)
vector<PointCloud<PointXYZRGB>::Ptr> PCDHandler::RANSAC(PointCloud<PointXYZRGB>::Ptr in_cloud) {
    ModelCoefficients::Ptr coefficients (new ModelCoefficients);
    PointIndices::Ptr inliers (new PointIndices);
    PointCloud<PointXYZRGB>::Ptr cloud_seg (new PointCloud<PointXYZRGB>);
    PointCloud<PointXYZRGB>::Ptr cloud_unseg (new PointCloud<PointXYZRGB>);

    //Create segmentation object
    SACSegmentation<PointXYZRGB> seg;
    seg.setOptimizeCoefficients (true);
    seg.setModelType (SACMODEL_PLANE);
    seg.setMethodType (SAC_RANSAC);
    seg.setDistanceThreshold (0.008);

    seg.setInputCloud (in_cloud);
    seg.segment (*inliers, *coefficients);
    
    if (inliers->indices.size() == 0) {
        PCL_ERROR ("Could not estimate a planar model for the input cloud.");
    }
    
    // std::cerr << "Model coefficients: " << coefficients->values[0] << " " 
    //                                   << coefficients->values[1] << " "
    //                                   << coefficients->values[2] << " " 
    //                                   << coefficients->values[3] << std::endl;

    // method 1 : new cloud with detected plane
    // copyPointCloud<PointXYZRGB>(*cloud_xyz, *inliers, *cloud_seg);
    
    // method 2: extract filter
    // create filtering object
    ExtractIndices<PointXYZRGB> extract;
    
    // inliers
    extract.setInputCloud(in_cloud);
    extract.setIndices(inliers);
    extract.setNegative(false);
    extract.filter(*cloud_seg);

    // outliers
    extract.setInputCloud(in_cloud);
    extract.setIndices(inliers);
    extract.setNegative(true);
    extract.filter(*cloud_unseg);

    vector<PointCloud<PointXYZRGB>::Ptr> ptrclouds;
    ptrclouds.push_back(cloud_seg);
    ptrclouds.push_back(cloud_unseg);

    return ptrclouds;
}