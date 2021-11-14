#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

void receive(const geometry_msgs::Twist& movement) {
	ROS_INFO("Got:\n"
			 "1) pos.linear: x= %f y= %f z= %f\n"
			 "2) pos.angular x= %f y= %f z= %f\n",
			 movement.linear.x, movement.linear.y, movement.linear.z,
			 movement.angular.x, movement.angular.y, movement.angular.z);
	return;
}

int main(int argc, char **argv) {
	// Имя ноды
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	// Подписываемся на топик "/turtle1/cmd_vel" с буфером в 1000 сообщений
	// и функцией обработчиком receive
	ros::Subscriber sub = n.subscribe("/turtle1/cmd_vel", 1000, receive);
	ros::spin();
	return 0;
}