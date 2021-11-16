#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

using namespace std;

void topic_reader (const std_msgs::Int32& message)
{
  // Выводим сообщение из топика
  ROS_INFO_STREAM(message.data);
  return;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle node;

  ROS_INFO("Ready to read topic.");
  ros::Subscriber sub = node.subscribe("sle_solver", 1000, topic_reader);

  ros::spin();
  return 0;
}
