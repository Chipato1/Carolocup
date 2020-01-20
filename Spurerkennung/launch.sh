roslaunch ueye_cam/launch/mono8.launch
rosrun image_proc rectify
rosrun vision vision_lanedetectionnode
rosrun image_view image_view image:=camera/image_raw