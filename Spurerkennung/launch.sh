#run camera
roslaunch src/ueye_cam/launch/mono8.launch
#run camera undistort
rosrun image_proc rectify
#run qr code detector
rosrun vision vision_startboxdetectionnode
#run lane detection node
rosrun vision vision_lanedetectionnode
#run stop line detection
rosrun vision vision_stoplinedetectionnode
#run parking lot detection
rosrun vision vision_parkinglotdetection
#show camera image
rosrun image_view image_view image:=camera/image_raw