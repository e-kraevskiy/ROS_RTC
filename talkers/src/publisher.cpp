
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{    
     // "publisher" - имя ноды для вызозова
     ros::init(argc, argv, "publisher");     
     ros::NodeHandle n;     
     //"/turtle1/cmd_vel" - имя топика, куда публикуються сообщения типа geometry_msgs::Twist
     // с буфером в 1000 сообщений
     ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);     
     // частота публикации - 1 сообщение в секунду
     ros::Rate loop_rate(1);     
     for (int t = 0; t < 20; t++){         
          // Формируем сообщение
          geometry_msgs::Twist pos;         
          pos.linear.x=1.5;         
          pos.angular.z=std::abs(2*sin(0.5*t));         

          ROS_INFO("Move to position:\n"             
                    "1) pos.linear: x= %f y=%f z=%f\n"
                    "2) pos.angular: x= %f y=%f z=%f\n",
                    pos.linear.x, pos.linear.y, pos.linear.z,
                    pos.angular.x, pos.angular.y, pos.angular.z);
          // Отправляем сообщение
          pub.publish(pos);        
          // Команда для поддержание необходимого loop_rate
          loop_rate.sleep();     
     }
     //ожидание завершения всех процессов ноды     
     ros::spinOnce();
     return 0;
}  
