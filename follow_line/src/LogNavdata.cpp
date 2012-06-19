#include "ardrone_brown/Navdata.h"
#include "ros/ros.h"

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//ofstream outfile("ros_workspace/follow_line/Log/LogNavdata.txt");
ofstream outfile;


void navdataUpdate(const ardrone_brown::Navdata::ConstPtr& navdata)
{
  time_t t;
  time(&t);
  outfile << ctime(&t) << endl;
  outfile << "Batterie: " << navdata->batteryPercent << endl;
  outfile << "RotX: " << navdata->rotX << endl;
  outfile << "RotY: " << navdata->rotY << endl;
  outfile << "RotZ: " << navdata->rotZ << endl;
  outfile << "Höhe: " << navdata->altd << endl;
  outfile << "vx: " << navdata->vx << endl;
  outfile << "vy: " << navdata->vy << endl;
  outfile << "vx: " << navdata->vz << endl;
  outfile << "Zeit seit Start: " << navdata->tm << endl << endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "LogNavdata");

  ros::NodeHandle node_handle;
  
  time_t t;
  time(&t);
  ostringstream ost;
  ost << "ros_workspace/follow_line/Log/LogNavdata";
  ost << ctime(&t);
  ost << ".txt";
  outfile.open(ost.str().c_str());

  ros::Subscriber navdata = node_handle.subscribe("/ardrone/navdata", 1000, navdataUpdate); 

  ros::spin();
}
