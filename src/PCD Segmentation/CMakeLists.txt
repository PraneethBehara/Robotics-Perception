cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Exercise1)
find_package(PCL 1.3 REQUIRED COMPONENTS common io visualization)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(ransac_exec RANSAC.cpp)
target_link_libraries(ransac_exec ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} pcl_segmentation -lpcl_filters pcl_visualization pcl_search)