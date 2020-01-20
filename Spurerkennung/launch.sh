roslaunch ueye_cam/launch/mono8.launch
rosrun image_proc rectify
rosrun vision vision_lanedetectionnode
