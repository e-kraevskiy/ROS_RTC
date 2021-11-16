#include "ros/ros.h"
#include "ke_service/SleSolver.h"
#include "std_msgs/Int32.h"

ros::Publisher publisher;

// функция обработчик
bool solve(ke_service::SleSolver::Request &req,
    ke_service::SleSolver::Response &res)
{
    res.sum = req.first + req.second;
    ROS_INFO("request:x=%d,y=%d",req.first,req.second);
    ROS_INFO("sending back response:[%d]",res.sum);

    // Публикуем результат в топик
    std_msgs::Int32 reply;
    reply.data = res.sum;
    publisher.publish(reply);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"sle_solver_server");
    ros::NodeHandle n;
    //подписываем товарища на чтение топика
    publisher = n.advertise <std_msgs::Int32> ("sle_solver", 1000);
    // ставим service на "прослушку" сервиса с названием "sle_solver" 
    ros::ServiceServer service = n.advertiseService("sle_solver", solve);
    ROS_INFO("READY TO SOLVE SLE");
    ros::spin();
    return 0;
}