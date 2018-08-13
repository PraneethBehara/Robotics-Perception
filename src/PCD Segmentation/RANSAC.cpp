#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/features/normal_3d.h> //required for kdtree
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace pcl;
using namespace std;

void displayCloud (PointCloud<PointXYZRGB>::Ptr cloud) {
    visualization::PCLVisualizer viewer ("Cloud Viewer");
    viewer.addPointCloud(cloud, "cloud");
    viewer.spin();
 }

PointCloud<PointXYZRGB>::Ptr PassThroughFilter(PointCloud<PointXYZRGB>::Ptr in_cloud) {
    PassThrough<PointXYZRGB> pass;
    PointCloud<PointXYZRGB>::Ptr out_cloud (new PointCloud<PointXYZRGB>());

    pass.setInputCloud (in_cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (-0.7,0.77);
    pass.setFilterLimitsNegative (true);
    pass.filter (*out_cloud);

    return out_cloud;
}

PointCloud<PointXYZRGB>::Ptr DownsamplePCD(PointCloud<PointXYZRGB>::Ptr in_cloud) {
    // Create the filtering object
    PointCloud<PointXYZRGB>::Ptr cloud_filtered (new PointCloud<PointXYZRGB>);
    VoxelGrid<PointXYZRGB> sor;
    sor.setInputCloud (in_cloud);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*cloud_filtered);

    cerr << "PointCloud before filtering: " << in_cloud->width * in_cloud->height 
        << " data points (" << getFieldsList (*in_cloud) << ")." << endl;

    cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
        << " data points (" << getFieldsList (*cloud_filtered) << ")." << endl;

    return cloud_filtered;
}

void SaveCloud(string filename, PointCloud<PointXYZRGB>::Ptr cloud, bool binary) {
    PCDWriter writer;
    writer.write<PointXYZRGB> (filename, *cloud, binary);
}

int main (int argc, char** argv)
{
    PointCloud<PointXYZRGB>::Ptr cloud (new PointCloud<PointXYZRGB>()); 
    PCDReader reader;
    reader.read ("tabletop.pcd", *cloud); 

    // displayCloud(cloud);
    // Voxel grid filter
    PointCloud<PointXYZRGB>::Ptr cloud_downsampled (new PointCloud<PointXYZRGB>());
    cloud_downsampled = DownsamplePCD(cloud);

    // displayCloud(cloud_downsampled);
    SaveCloud ("tabletop_downsampled.pcd", cloud_downsampled, false);

    // PassThrough filter
    PointCloud<PointXYZRGB>::Ptr cloud_passed(new PointCloud<PointXYZRGB>); 
    cloud_passed = PassThroughFilter(cloud_downsampled);
    
    SaveCloud ("tabletop_passfilter.pcd", cloud_passed, false);

    // displayCloud(cloud_passed);

    // RANSAC plane segmentation
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

    seg.setInputCloud (cloud_passed);
    seg.segment (*inliers, *coefficients);
    
    if (inliers->indices.size() == 0) {
        PCL_ERROR ("Could not estimate a planar model for the input cloud.");
        return -1;
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
    extract.setInputCloud(cloud_passed);
    extract.setIndices(inliers);
    extract.setNegative(false);
    extract.filter(*cloud_seg);

    // outliers
    extract.setInputCloud(cloud_passed);
    extract.setIndices(inliers);
    extract.setNegative(true);
    extract.filter(*cloud_unseg);

    SaveCloud("table_segmented.pcd", cloud_seg, false);
    SaveCloud("objects_segmented.pcd", cloud_unseg, false);
    
    // displayCloud(cloud_seg);
    // displayCloud(cloud_unseg);
    
    // Segmentation for table top items
    // Create Kd-tree data struct for unsegmented point cloud
    search::KdTree<PointXYZRGB>::Ptr tree (new search::KdTree<PointXYZRGB> ());
    tree->setInputCloud(cloud_unseg);

    // Create empty list of clusters and euclidean cluster extraction object
    vector<PointIndices> cluster_indices; //contains all clusters after extraction 
    EuclideanClusterExtraction<PointXYZRGB> ec;
    ec.setClusterTolerance(0.02); //2cm
    ec.setMinClusterSize(100);
    ec.setMaxClusterSize(25000);
    ec.setSearchMethod(tree);
    ec.setInputCloud(cloud_unseg);
    ec.extract(cluster_indices);

    vector<PointIndices>::const_iterator itr;

    // Create new PC's for each cluster and save
    int i = 0;
    for (itr=cluster_indices.begin(); itr!= cluster_indices.end(); ++itr){
        PointCloud<PointXYZRGB>::Ptr cluster_cloud (new PointCloud<PointXYZRGB>);
        vector<int>::const_iterator pit;
        for (pit=itr->indices.begin(); pit!=itr->indices.end(); ++pit){
            cluster_cloud->points.push_back (cloud_unseg->points[*pit]);
        } 
        cluster_cloud->width = cluster_cloud->points.size();
        cluster_cloud->height = 1;
        cluster_cloud->is_dense = true;

        // save cloud
        cout << "Saving cluster cloud" << i << endl;
        stringstream ss;
        ss << "cluster_cloud_" << i << ".pcd";
        SaveCloud(ss.str(), cluster_cloud, false);
        
        // increment to next cluster
        i++;
    }
    return (0);
}