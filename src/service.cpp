#include "ros/ros.h"
#include "ke_client_server/SleSolver.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32MultiArray.h"

ros::Publisher publisher;

// функция обработчик
bool solve(ke_client_server::SleSolver::Request &req,
    ke_client_server::SleSolver::Response &res)
{
    float sum1 = req.input1 + req.input2;
    float sum2 = req.input3 + req.input4;
    ROS_INFO("request:1=%f,2=%f,3=%f,4=%f",req.input1,req.input2,req.input3,req.input4);
    ROS_INFO("sending back response:[%f],[%f]",sum1,sum2);
    res.output.push_back(sum1);
    res.output.push_back(sum2);


    // Публикуем результат в топик
    std_msgs::Float32MultiArray reply;
    reply.data = res.output;
    publisher.publish(reply);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"sle_solver_server");
    ros::NodeHandle n;
    //подписываем товарища на чтение топика
    publisher = n.advertise <std_msgs::Float32MultiArray> ("sle_solver", 1000);
    // ставим service на "прослушку" сервиса с названием "sle_solver" 
    ros::ServiceServer service = n.advertiseService("sle_solver", solve);
    ROS_INFO("READY TO SOLVE SLE");
    ros::spin();
    return 0;
}

