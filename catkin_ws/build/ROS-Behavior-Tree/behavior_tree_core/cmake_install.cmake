# Install script for directory: /home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/src/ROS-Behavior-Tree/behavior_tree_core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/behavior_tree_core/action" TYPE FILE FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/src/ROS-Behavior-Tree/behavior_tree_core/action/BT.action")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/behavior_tree_core/msg" TYPE FILE FILES
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTAction.msg"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTActionGoal.msg"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTActionResult.msg"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTActionFeedback.msg"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTGoal.msg"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTResult.msg"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/behavior_tree_core/msg/BTFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/behavior_tree_core/cmake" TYPE FILE FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/build/ROS-Behavior-Tree/behavior_tree_core/catkin_generated/installspace/behavior_tree_core-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/include/behavior_tree_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/roseus/ros/behavior_tree_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/common-lisp/ros/behavior_tree_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/share/gennodejs/ros/behavior_tree_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/lib/python2.7/dist-packages/behavior_tree_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/devel/lib/python2.7/dist-packages/behavior_tree_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/build/ROS-Behavior-Tree/behavior_tree_core/catkin_generated/installspace/behavior_tree_core.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/behavior_tree_core/cmake" TYPE FILE FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/build/ROS-Behavior-Tree/behavior_tree_core/catkin_generated/installspace/behavior_tree_core-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/behavior_tree_core/cmake" TYPE FILE FILES
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/build/ROS-Behavior-Tree/behavior_tree_core/catkin_generated/installspace/behavior_tree_coreConfig.cmake"
    "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/build/ROS-Behavior-Tree/behavior_tree_core/catkin_generated/installspace/behavior_tree_coreConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/behavior_tree_core" TYPE FILE FILES "/home/chipato/Desktop/Carolo_Git/Carolocup/catkin_ws/src/ROS-Behavior-Tree/behavior_tree_core/package.xml")
endif()

