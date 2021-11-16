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
        float in[4];
        std::cout<<"1:";    
        std::cin>>in[0];
        std::cout<<"2:";    
        std::cin>>in[1];
        std::cout<<"3:";    
        std::cin>>in[2];
        std::cout<<"4:";    
        std::cin>>in[3];
        
        srv.request.input1 = in[0];
        srv.request.input2 = in[1];
        srv.request.input3 = in[2];
        srv.request.input4 = in[3];
        // for (int i = 0; i < 6; i ++)
        //     srv.request.inputi = in[i];
        
        

        if (client.call(srv))
        {
            std::cout<<"output1="<<srv.response.output[0]<<std::endl;
            std::cout<<"output2="<<srv.response.output[1]<<std::endl;
        }
        else
        {
            std::cout<<"Failed to call service hhhhhhhhhhhhhhhhhhhhhhhhhhh"<<std::endl;
            return 1;
        }
    }

    return 0;
}