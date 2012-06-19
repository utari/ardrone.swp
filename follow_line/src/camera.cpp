#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/CvBridge.h>
#include <std_srvs/Empty.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  sensor_msgs::CvBridge bridge;
  try
  {
    cvShowImage("view", bridge.imgMsgToCv(msg, "bgr8"));
  }
  catch (sensor_msgs::CvBridgeException& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "camera_listener_unsers");
  ros::NodeHandle nh;

  //ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>("/ardrone/togglecam");
  //std_srvs::Empty srv;
  //client.call(srv);

  cvNamedWindow("view");
  cvStartWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/ardrone/image_raw", 1, imageCallback);
  ros::spin();
  cvDestroyWindow("view");
}
