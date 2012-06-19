#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"
#include "std_msgs/String.h"

#include "ardrone_brown/Navdata.h"
#include "ar_recog/Tags.h"
#include "ar_recog/Tag.h"
#include "ardrone_brown/Navdata.h"

#include "follow_line/LinePos.h"
#include "Delta.h"

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;


geometry_msgs::Twist twist;

ros::Publisher pub;
int altd = -1;

int width = 160;
int height = 120;

Delta lxDelta;
Delta lyDelta;
Delta lzDelta;
Delta azDelta;

void navdataUpdate(const ardrone_brown::Navdata::ConstPtr& navdata)
{
  altd = navdata->altd;
}
void handleLine(const follow_line::LinePos::ConstPtr& msg)
{
  if(msg->x == width/2 && msg->y == height/2)
  {
    //keine Linie wird erkannt
    twist.linear.x = 0;
    twist.linear.y = 0;
    twist.linear.z = 0;
    twist.angular.z = 0;

    ostringstream ostr;
    ostr << "linear.x: " << twist.linear.x << endl;
    ostr << "linear.y: " << twist.linear.y << endl << endl;
    ostr << "linear.z " << twist.linear.z << endl;
    ostr << "angular.z " << twist.angular.z << endl;
    ostr << "altd: " << altd << endl;
    ROS_INFO(ostr.str().c_str());
    pub.publish(twist);
    return;
  }
  //twist.angular.z = msg->angle / 9000;

  float z = 0;
  if(abs(msg->angle) > 7000)
    z = msg->angle > 0 ? 0.3 : -0.3;
  else if(abs(msg->angle) > 4000)
    z = msg->angle > 0 ? 0.2 : -0.2;
  else if(abs(msg->angle) > 500)
    z = msg->angle > 0 ? 0.1 : -0.1;

  twist.angular.z = azDelta.get_velocity(z);

  //Fliege immer nach vorne, wenn Linie erkannt wurde
  twist.linear.x = lxDelta.get_velocity(0.05);

  if(msg->x > width/2 + 5)
   twist.linear.y = lyDelta.get_velocity(0.1);
  else if(msg->y < height/2 - 5)
   twist.linear.y = lyDelta.get_velocity(-0.1);
  else
   twist.linear.y = lyDelta.get_velocity(0);

  if(altd > 900)
   twist.linear.z = lzDelta.get_velocity(-0.2);
  else if(altd < 800)
   twist.linear.z = lzDelta.get_velocity(0.2);
  else
   twist.linear.z = lzDelta.get_velocity(0);

  ostringstream ostr;
  ostr << "linear.x: " << twist.linear.x << endl;
  ostr << "linear.y: " << twist.linear.y << endl << endl;
  ostr << "linear.z " << twist.linear.z << endl;
  ostr << "angular.z " << twist.angular.z << endl;
  ostr << "altd: " << altd << endl;
  ostr << "x:    " << msg->x << endl;
  ostr << "y:    " << msg->y << endl;
  ROS_INFO(ostr.str().c_str());
    pub.publish(twist);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "follow_line2");

  twist.linear.x = 0;
  twist.linear.y = 0;
  twist.linear.z = 0;
  twist.angular.z = 0;

  ros::NodeHandle node_handle;
  pub = node_handle.advertise<geometry_msgs::Twist>("cmd_vel", 1000); 
  ros::Subscriber sub = node_handle.subscribe("LinePos",1000, handleLine);

  ros::Subscriber navdata = node_handle.subscribe("/ardrone/navdata", 1000, navdataUpdate);

  pub.publish(twist);

  ros::spin();
}
