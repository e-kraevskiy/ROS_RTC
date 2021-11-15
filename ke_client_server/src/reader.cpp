#include "ros/ros.h"
#include "ke_service/SleSolver.h"

bool add(ke_service::SleSolver::Request &req,
    ke_service::SleSolver::Response &res)
{
    res.sum = req.first + req.second;
    ROS_INFO("request:x=%d,y=%d",req.first,req.second);
    ROS_INFO("sending back response:[%d]",res.sum);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"add_two_ints_server");
    ros::NodeHandle n;
    
    ros::ServiceServer service=n.advertiseService("add_two_ints",add);
    ROS_INFO("READY TO ADD TWO INTS");
    ros::spin();
    return 0;
}