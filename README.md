# ROS RTC
### Репозиторий для выполнения задач по дисциплине: "Управление робототехническими системами"
#### СПбПУ, 4 курс, кафедра: "Мехатроника и робототехника" при ЦНИИ РТК

---

### Задание 1 - Разработка собственного пакета с сервисом, издателем и подписчиком

Данный пакет решает СЛАУ второго порядка. 
Для этого нужно обратиться к сервису с запросом из шести чисел (коэффициентов уравнения).
Напимер запрос с параметрами "1 2 3 4 5 6" Я вляется следующей системой уравнений:
> x + 2y = 3
> 
> 4x + 5y = 6
Для запуска необходимо:
- Слонировать данные из репозитория в src рабочего пространство ROS:

Например, если рабочее пространсво это: ~/workspace, то в папке ~/workspace/src/ должна лежать папка ke_client_server

- Собрать пакет из рабочего пространства
- В первом терминале запустить `roscore`
- Во втором терминале запустить сервис:

`rosrun ke_client_server service`

(Специфичное название пакета во избежание совпадения с другими студентами, а ke - Краевский Евгений)
- В третьем терминале запустить подписчика топика, в который публикует данные сервис:

`rosrun ke_client_server subscriber`

- И в последнем терминале можно отпавлять запрос сервису командой: 

`rosservice call /sle_solver 1 2 3 4 5 6`

Где "1 2 3 4 5 6" - коэффициенты СЛАУ

Для проверки можно воспользоваться следующими примерами:

`rosservice call /sle_solver 1 2 3 4 5 6`

Решение: -1 2 

`rosservice call /sle_solver 1 1 1 1 1 1`

Нет корней 

`rosservice call /sle_solver 1 9 9 1 9 5`

Нет корней 

`rosservice call /sle_solver 4 6 9 5 1 18`

Решение: 3.81 -1.04 

`rosservice call /sle_solver 5 0 5 4 1 1`

Решение: 1 -3

---

### Задание 2 - SLAM

Суть задания очень простая - нужно запустить в симуляторе робот TurtleBot3 и построить карту методом SLAM. 
Мир, карту которого строит робот, должен быть не стандартный из пакета turtlebot3_gazebo, а лично вами смоделированная в Gazebo.
В качестве моедели робота используйте waffle_pi. Необходимо визуализировать процесс построения карты в rviz, отобразить показания лидара и камеры.
Построение карты SLAM должно осуществляться не в ручную (без  Teleoperation Node ), а с помощью стека навигации (применить Navigation Node).

(_Данного задания в репозитории нет, т.к. выполнянлось и сдавалось оно с использованием gazebo и rviz_)
