#include "ros/ros.h"
#include "ke_client_server/SleSolver.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"sle_solver_publisher");

    ros::NodeHandle n;
    // подписываем client на отпарвку сообщений в сервис "solve_sle"
    ros::ServiceClient client = n.serviceClient<ke_client_server::SleSolver>("sle_solver");
    ke_client_server::SleSolver srv;

    while (ros::ok())
    {
        int a,b;
        std::cout<<"input the first num:";    
        std::cin>>a;
        std::cout<<"input the second num:";    
        std::cin>>b;
        
        srv.request.first = a;
        srv.request.second = b;

        if (client.call(srv))
        {
            std::cout<<"sum="<<srv.response.sum<<std::endl;
        }
        else
        {
            std::cout<<"Failed to call service hhhhhhhhhhhhhhhhhhhhhhhhhhh"<<std::endl;
            return 1;
        }
    }

    return 0;
}