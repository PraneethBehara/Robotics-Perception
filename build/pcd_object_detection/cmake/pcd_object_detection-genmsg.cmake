# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pcd_object_detection: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ipcd_object_detection:/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pcd_object_detection_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" NAME_WE)
add_custom_target(_pcd_object_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pcd_object_detection" "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" "sensor_msgs/PointField:std_msgs/Header:sensor_msgs/PointCloud2"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pcd_object_detection
  "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pcd_object_detection
)

### Generating Services

### Generating Module File
_generate_module_cpp(pcd_object_detection
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pcd_object_detection
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pcd_object_detection_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pcd_object_detection_generate_messages pcd_object_detection_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" NAME_WE)
add_dependencies(pcd_object_detection_generate_messages_cpp _pcd_object_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pcd_object_detection_gencpp)
add_dependencies(pcd_object_detection_gencpp pcd_object_detection_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pcd_object_detection_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(pcd_object_detection
  "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pcd_object_detection
)

### Generating Services

### Generating Module File
_generate_module_eus(pcd_object_detection
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pcd_object_detection
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(pcd_object_detection_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(pcd_object_detection_generate_messages pcd_object_detection_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" NAME_WE)
add_dependencies(pcd_object_detection_generate_messages_eus _pcd_object_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pcd_object_detection_geneus)
add_dependencies(pcd_object_detection_geneus pcd_object_detection_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pcd_object_detection_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pcd_object_detection
  "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pcd_object_detection
)

### Generating Services

### Generating Module File
_generate_module_lisp(pcd_object_detection
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pcd_object_detection
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pcd_object_detection_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pcd_object_detection_generate_messages pcd_object_detection_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" NAME_WE)
add_dependencies(pcd_object_detection_generate_messages_lisp _pcd_object_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pcd_object_detection_genlisp)
add_dependencies(pcd_object_detection_genlisp pcd_object_detection_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pcd_object_detection_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(pcd_object_detection
  "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pcd_object_detection
)

### Generating Services

### Generating Module File
_generate_module_nodejs(pcd_object_detection
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pcd_object_detection
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(pcd_object_detection_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(pcd_object_detection_generate_messages pcd_object_detection_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" NAME_WE)
add_dependencies(pcd_object_detection_generate_messages_nodejs _pcd_object_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pcd_object_detection_gennodejs)
add_dependencies(pcd_object_detection_gennodejs pcd_object_detection_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pcd_object_detection_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pcd_object_detection
  "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointField.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pcd_object_detection
)

### Generating Services

### Generating Module File
_generate_module_py(pcd_object_detection
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pcd_object_detection
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pcd_object_detection_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pcd_object_detection_generate_messages pcd_object_detection_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/media/praneeth/Linux/Personal/ros_packages/perception_ws/src/pcd_object_detection/msg/SegmentedClusters.msg" NAME_WE)
add_dependencies(pcd_object_detection_generate_messages_py _pcd_object_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pcd_object_detection_genpy)
add_dependencies(pcd_object_detection_genpy pcd_object_detection_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pcd_object_detection_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pcd_object_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pcd_object_detection
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(pcd_object_detection_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(pcd_object_detection_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pcd_object_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pcd_object_detection
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(pcd_object_detection_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(pcd_object_detection_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pcd_object_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pcd_object_detection
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(pcd_object_detection_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(pcd_object_detection_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pcd_object_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pcd_object_detection
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(pcd_object_detection_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(pcd_object_detection_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pcd_object_detection)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pcd_object_detection\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pcd_object_detection
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(pcd_object_detection_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(pcd_object_detection_generate_messages_py sensor_msgs_generate_messages_py)
endif()
