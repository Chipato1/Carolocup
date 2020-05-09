cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(lidar)

##############################################################################
# Find dependencies
##############################################################################


set(RPLIDAR_SDK_PATH "./sdk/")

FILE(GLOB RPLIDAR_SDK_SRC 
  "${RPLIDAR_SDK_PATH}/src/arch/linux/*.cpp"
  "${RPLIDAR_SDK_PATH}/src/hal/*.cpp"
  "${RPLIDAR_SDK_PATH}/src/*.cpp"
)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosconsole
  sensor_msgs
  geometry_msgs
  tf
  laser_geometry
  filters
  message_generation
)

find_package(PCL 1.2 REQUIRED)

find_package(Boost REQUIRED COMPONENTS system)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${RPLIDAR_SDK_PATH}/include
  ${RPLIDAR_SDK_PATH}/src
)

link_directories(
  ${PCL_LIBRARY_DIRS}
)

add_definitions(
  ${PCL_DEFINITIONS}
)


##############################################################################
# Add service definitions
##############################################################################

add_service_files(FILES
AssembleScans.srv)

generate_messages(DEPENDENCIES sensor_msgs std_msgs)

##############################################################################
# Build
##############################################################################

add_executable(object_detection src/object_detection.cpp)
target_link_libraries(object_detection ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(laser_scan_assembler src/laser_scan_assembler.cpp)
target_link_libraries(laser_scan_assembler ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(periodic_snapshotter src/periodic_snapshotter.cpp)
target_link_libraries(periodic_snapshotter ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(rplidar_ros src/rplidar_ros.cpp ${RPLIDAR_SDK_SRC})
target_link_libraries(rplidar_ros ${catkin_LIBRARIES})

