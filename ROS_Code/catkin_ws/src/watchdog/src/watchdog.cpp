#include "watchdog.h"
#include "ros/ros.h"
#include "std_msgs/UInt8.h"

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "watchdog");
  ros::NodeHandle nh;
  ros::Publisher watchdog_pub = nh.advertise<std_msgs::UInt8>("watchdog_error", 1000);

  ros::Rate r(150);
  std_msgs::UInt8 err;
  err.data = 0

  redi::ipstream proc("rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0", redi::pstreams::pstdout | redi::pstreams::pstderr);
  std::string line;
  
  

  while (ros::ok())
  {
    number.data = 0;
    ros::spinOnce();
    r.sleep();
    
    if (std::getline(proc.out(), line))
        std::cout << "stdout: " << line << '\n';
  
    if (std::getline(proc.err(), line))
        std::cout << "stderr: " << line << '\n';


    watchdog_pub.publish(err);
    loop_rate.sleep();
  }
  return 0;
}

