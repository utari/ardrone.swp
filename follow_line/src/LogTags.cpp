#include "ros/ros.h"
#include "ar_recog/Tags.h"
#include "ar_recog/Tag.h"

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
ofstream outfile;

void handleTag(const ar_recog::Tags::ConstPtr& msg)
{
  time_t t;
  time(&t);
  outfile << ctime(&t) << endl;
  outfile << "Anzahl der Tags: " << msg->tag_count << endl;

  if(msg->tag_count > 0)
  {
    outfile  << "image_width: " << msg->image_width << endl;
    outfile  << "image_height: " << msg->image_height << endl;
    outfile  << "angle_of_view: " << msg->angle_of_view << endl;

    for(size_t i = 0; i < msg->tag_count; ++i)
    {
      outfile << "distance: " << msg->tags[i].distance << endl;
      outfile << "diameter: " << msg->tags[i].diameter << endl;
      outfile << "xRot: " << msg->tags[i].xRot << endl;
      outfile << "yRot: " << msg->tags[i].yRot << endl;
      outfile << "zRot: " << msg->tags[i].zRot << endl;

      float cx = 0;
      float cy = 0;
      for(int i = 0; i < 7; i+=2)
      {
        cx = cx + msg->tags[i].cwCorners[i];
        cy = cy + msg->tags[i].cwCorners[i+1];
      }
      cx = cx / 4.0 / msg->image_width;
      cy = cy / 4.0 / msg->image_height;

      outfile << "cx: " << cx << endl;
      outfile << "cy: " << cy << endl;
    }
    outfile << endl;
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "LogTags");

  ros::NodeHandle node_handle;
  
  time_t t;
  time(&t);
  ostringstream ost;
  ost << "ros_workspace/follow_line/Log/LogTags";
  ost << ctime(&t);
  ost << ".txt";
  outfile.open(ost.str().c_str());

  ros::Subscriber sub = node_handle.subscribe("tags",1000, handleTag);

  ros::spin();
}
