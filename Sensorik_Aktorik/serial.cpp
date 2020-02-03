#include "serial.h"
#include "aktorik.h"

std_msgs::Float32 rpm_msg;
std_msgs::UInt16 tof_front_msg, tof_left_msg, tof_right_msg, tof_cross_msg, tof_back_msg;
std_msgs::Bool error_msg, rc_mode_msg;

ros::Publisher pub_rpm("sns_wheelRpm", &rpm_msg);
ros::Publisher pub_tof_front("sns_distanceFront", &tof_front_msg);
ros::Publisher pub_tof_left("sns_distanceLeft", &tof_left_msg);
ros::Publisher pub_tof_right("sns_distanceRight", &tof_right_msg);
ros::Publisher pub_tof_cross("sns_distanceCross", &tof_cross_msg);
ros::Publisher pub_tof_back("sns_distanceBack", &tof_back_msg);
ros::Publisher pub_rc_mode("rc_mode", &rc_mode_msg);
ros::Publisher pub_error("error", &error_msg);

ros::Subscriber<std_msgs::Float32> sub_servo("ctl_servoAngle", servo_cb);
ros::Subscriber<std_msgs::Int16> sub_motor("ctl_motorRpm", motor_cb);      
ros::Subscriber<std_msgs::UInt8> sub_light_l("trj_flashLeft", lichtLinks_cb);
ros::Subscriber<std_msgs::UInt8> sub_light_r("trj_flashRight", lichtRechts_cb);
ros::Subscriber<std_msgs::UInt8> sub_light_b("trj_breakLight", lichtBremse_cb);
ros::Subscriber<std_msgs::UInt8> sub_light_rem("trj_remoteLight", lichtRemote_cb);


void init_ros(){
  node.initNode();
  node.advertise(pub_rpm);
  node.advertise(pub_tof_front);
  node.advertise(pub_tof_left);
  node.advertise(pub_tof_right);
  node.advertise(pub_tof_cross);
  node.advertise(pub_tof_back);
  node.advertise(pub_rc_mode);
  node.advertise(pub_error);

  node.subscribe(sub_servo);
  node.subscribe(sub_motor);
  node.subscribe(sub_light_l);
  node.subscribe(sub_light_r);
  node.subscribe(sub_light_b);
  node.subscribe(sub_light_rem);
}

//Callbacks
void servo_cb(const std_msgs::Float32& cmd_msg){
  servo_bewegung(cmd_msg.data);
}
void motor_cb(const std_msgs::Int16& cmd_msg){
  motor_bewegung(cmd_msg.data);
}
void lichtLinks_cb(const std_msgs::UInt8& light_state){
  state_light_r = light_state.data;
}
void lichtRechts_cb(const std_msgs::UInt8& light_state){
  state_light_l = light_state.data;
}
void lichtBremse_cb(const std_msgs::UInt8& light_state){
  state_light_b = light_state.data;
}
void lichtRemote_cb(const std_msgs::UInt8& light_state){
  state_light_rem = light_state.data;
}


/*void rpm_publish(float rpm){  
  rpm_msg.data = rpm;
  pub_rpm.publish(&rpm_msg);
}
*/

void tof_publish(uint16_t front, uint16_t left, uint16_t right, uint16_t cross, uint16_t back){  
  tof_front_msg.data = front;
  pub_tof_front.publish(&tof_front_msg);
  
  tof_left_msg.data = left;
  pub_tof_left.publish(&tof_left_msg);
  
  tof_right_msg.data = right;
  pub_tof_right.publish(&tof_right_msg);
  
  tof_cross_msg.data = cross;
  pub_tof_cross.publish(&tof_cross_msg);
  
  tof_back_msg.data = back;
  pub_tof_back.publish(&tof_back_msg);
}

void rc_mode_publish(boolean RCmode){  
  rc_mode_msg.data = RCmode;
  pub_rc_mode.publish(&rc_mode_msg);
}

void error_publish(boolean err){  
  error_msg.data = err;
  pub_error.publish(&error_msg);
}
