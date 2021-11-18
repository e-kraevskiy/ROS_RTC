#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include <iostream>

using namespace std;

void topic_reader (const std_msgs::Float32MultiArray& message)
{
  // Выводим сообщение из топика
  // if (message.get_data_size() == 0)
  // if (message.has_header == false)
  // if (message.data_length == 0)
  // {
  //   ROS_INFO("No solutions");
  //   return;
  // }
  ROS_INFO("x = %f, y = %f", message.data[0], message.data[1]);
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
