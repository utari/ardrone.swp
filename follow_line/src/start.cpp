#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"
#include "std_msgs/String.h"
#include "ardrone_brown/Navdata.h"
//#include "sensor_msgs/image.h"

#include <time.h>
#include <stdio.h>
#include <iostream>

geometry_msgs::Twist twist;


bool bump = false;

float akku = 0;
bool info = false;

void steuern(ros::Publisher pub, float x, float y, float z, float ax, float ay, float az)
{
    twist.linear.x = x;
    twist.linear.y = y;
    twist.linear.z = z;
    twist.angular.x = ax;
    twist.angular.y = ay;
    twist.angular.z = az;
    pub.publish(twist);
}

void navdataUpdate(const ardrone_brown::Navdata::ConstPtr& navdata)
{
  akku = navdata->batteryPercent;
  info = true;
}

//void imageUpdate(const sensor_msgs::Image::ConstPtr& image)
//{

//}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "start");

  ros::NodeHandle node_handle;

  ros::Publisher pub = node_handle.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

/*  ros::Publisher reset = node_handle.advertise<std_msgs::Empty>("ardrone/reset", 1000);

  ros::Publisher takeoff = node_handle.advertise<std_msgs::Empty>("ardrone/takeoff",1000);

  ros::Publisher land = node_handle.advertise<std_msgs::Empty>("ardrone/land", 1000);
  
//  ros::Subscriber image = node_handle.subscibe("/ardrone/image_raw", 1000, imageUpdate);

  ros::Subscriber navdata = node_handle.subscribe("/ardrone/navdata", 1, navdataUpdate);
*/


  twist.linear.x = 0.1;
  twist.linear.y = 0;
  twist.linear.z = 0;
  twist.angular.z = 0;

  time_t t1 = time(NULL);
  time_t t2;
  ros::Rate loop_rate(40);
  while(ros::ok())
  {
    t2 = time(NULL);
    if(t2 - t1 > 1)
    {
      ROS_INFO("Twist l.x 0");
      twist.linear.x = 0;
    }
    pub.publish(twist);
    loop_rate.sleep();
  }
  //while(!info) {}

  //std::ostringstream out;
  //out << akku;
  //ROS_INFO("Akku: %s", out.str().c_str());

 /* time_t t1 = time(NULL);
  time_t t2;
  std_msgs::String msg;

  ros::Rate loop_rate(40);
  int t = 2;
  while(ros::ok())
  {*/
    //while(!info) {}
    //std::ostringstream out;
    //out << akku;
    //ROS_INFO("Akku: %s", out.str().c_str());

    /*t2 = time(NULL);
    if(t2 - t1 < t * 1)
    {
      ROS_INFO("reset");
      reset.publish(msg);
    }
    else if(t2 - t1 < t * 3)
    {
      ROS_INFO("takeoff");
      takeoff.publish(msg);
    }*//*
t2 = time(NULL);
    if(t2 - t1 < t * 1)
    {
      ROS_INFO("+ linear.y");
      steuern(pub, 0, 0.3, 0, 0, 0, 0);
    }

    else if(t2 - t1 < t * 2)
    {
      ROS_INFO("- lineary");
      steuern(pub, 0, -0.3, 0, 0, 0, 0);
    }
    else
      break;
    loop_rate.sleep();
  }
  steuern(pub, 0, 0, 0, 0, 0, 0);

  ROS_INFO("land");
  land.publish(msg);

  steuern(pub, 0, 0, 0, 0, 0, 0);

  ros::spin();*/
}
