cmake_minimum_required(VERSION 2.8.3)
project(pcd_object_detection)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    pcl_conversions
    pcl_ros
    sensor_msgs
    roslint
    message_generation
) 

add_message_files(
  FILES
  SegmentedClusters.msg
 )

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

catkin_package(
# INCLUDE_DIRS include
# LIBRARIES pcd_object_detection
  CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs pcl_conversions pcl_msgs pcl_ros message_runtime
  DEPENDS boost_system PCL 
# DEPENDS system_lib
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(ransac_helper src/ransac_helper.cpp)
add_executable(euclidean_clustering src/euclidean_clustering.cpp)

add_dependencies(ransac_helper ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(euclidean_clustering ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(ransac_helper ${catkin_LIBRARIES})
target_link_libraries(euclidean_clustering ${catkin_LIBRARIES})

roslint_cpp(src/ransac_helper.cpp)
roslint_cpp(src/euclidean_clustering.cpp)
