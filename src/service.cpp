#include "ros/ros.h"
#include "ke_client_server/SleSolver.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32MultiArray.h"
#include <iostream>


ros::Publisher publisher;

// функция обработчик
bool solve(ke_client_server::SleSolver::Request &req,
    ke_client_server::SleSolver::Response &res)
{
    int n = 2;  //Порядок системы уравнений
    float a[n][n], b[n], x[n];

    a[0][0] = req.a11;
    a[0][1] = req.a12;
    b[0] = req.b1;
    a[1][0] = req.a21;
    a[1][1] =req.a22;
    b[1] = req.b2;

    float max;
    int k, index;
    const float eps = 0.00001;  // точность
    k = 0;
    while (k < n)
    {
      // Поиск строки с максимальным a[i][k]
      max = std::abs(a[k][k]);
      index = k;
      for (int i = k + 1; i < n; i++)
      {
        if (std::abs(a[i][k]) > max)
        {
          max = std::abs(a[i][k]);
          index = i;
        }
      }
      // Перестановка строк
      if (max < eps)
      {
        // нет ненулевых диагональных элементов
        std::cout << "No solutions" << std::endl;
        return true;
      }
      for (int j = 0; j < n; j++)
      {
        float temp = a[k][j];
        a[k][j] = a[index][j];
        a[index][j] = temp;
      }
      float temp = b[k];
      b[k] = b[index];
      b[index] = temp;
      // Нормализация уравнений
      for (int i = k; i < n; i++)
      {
        float temp = a[i][k];
        if (std::abs(temp) < eps) continue; // для нулевого коэффициента пропустить
        for (int j = 0; j < n; j++)
          a[i][j] = a[i][j] / temp;
        b[i] = b[i] / temp;
        if (i == k)  continue; // уравнение не вычитать само из себя
        for (int j = 0; j < n; j++)
          a[i][j] = a[i][j] - a[k][j];
        b[i] = b[i] - b[k];
      }
      k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
      x[k] = b[k];
      for (int i = 0; i < k; i++)
        b[i] = b[i] - a[i][k] * x[k];
    }

    // ROS_INFO("[%f %f]", x[0], x[1]);
    res.result.push_back(x[0]);
    res.result.push_back(x[1]);


    // Публикуем результат в топик
    std_msgs::Float32MultiArray reply;
    reply.data = res.result;
    publisher.publish(reply);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"sle_server");
    ros::NodeHandle n;
    //подписываем товарища на чтение топика
    publisher = n.advertise <std_msgs::Float32MultiArray> ("sle_solver", 1000);
    // ставим service на "прослушку" сервиса с названием "sle_solver" 
    ros::ServiceServer service = n.advertiseService("sle_solver", solve);
    ROS_INFO("READY TO SOLVE SLE");
    ros::spin();
    return 0;
}

