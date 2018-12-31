 #include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <sstream>
#include "ros/console.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "publisher");

    ros::NodeHandle nh; //Changed "Node" to "nh"
    ros::Subscriber sub;


    ros::Publisher pub = nh.advertise<std_msgs::String>("game",10);  //old -> pub= node.advertise<std_msgs::String>("game", 10);
    ros::Rate loop_rate(5);

    std::string guess;
    std_msgs::String msg;


  while (ros::ok()) //While loop moved to inside main
{
    ROS_INFO("YOUR GUESS: ");
    std::cin>>guess;
    msg.data=guess;

    pub.publish(msg);

    loop_rate.sleep(); //old -> ros::spinOnce();


}
//ros::spin(); Changed this
return 0;
}
