#include "ros/ros.h"
#include "irobot_create_2_1/SensorPacket.h"
#include "geometry_msgs/Twist.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

template<class T>
inline T max(T a, T b) { return a > b ? a : b; }
template<class T>
inline T min(T a, T b) { return a < b ? a : b; }

// globals
bool newInfo = false;
// updated on receiving data
int lSensorVal = 0;
int lfSensorVal = 0;
int rfSensorVal = 0;
int rSensorVal = 0;
bool bump = false;

geometry_msgs::Twist twist;

void receiveSensorUpdate(const irobot_create_2_1::SensorPacket::ConstPtr& sensorPacket)
{
    lSensorVal = sensorPacket->cliffLeftSignal;
    lfSensorVal = sensorPacket->cliffFrontLeftSignal;
    rfSensorVal = sensorPacket->cliffFrontRightSignal;
    rSensorVal = sensorPacket->cliffRightSignal;
    bump = sensorPacket->bumpLeft || sensorPacket->bumpRight;
    newInfo = true;
}

void steerRobot(ros::Publisher pub, float speed, float rotation)
{
    // twist.linear.x is speed; positive is forward
    // twist.angular.z is rotation; positive is CCW
    twist.linear.x = speed;
    twist.linear.y = 0;
    twist.linear.z = 0;
    twist.angular.x = 0;
    twist.angular.y = 0;
    twist.angular.z = rotation;
    pub.publish(twist);
}

float dtrace(const char* s, float x)
{
    ROS_INFO("%s",s);
    //ROS_INFO("%s",x);
    return x;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "follow_line");

  ros::NodeHandle node_handle;



  // constants
  float maxSpeed = 0.075f;
  float speedDecayRate = 1.5f;  // makes speed -> speed/speedDecayRate
  float maxTurn = 0.5f;

  // init
  ros::Publisher pub = node_handle.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber sub = node_handle.subscribe("sensorPacket", 1000, receiveSensorUpdate);

  // calibration
  ROS_INFO("Calibrating sensors now.  Make sure robot is over line.");
  int lMin = 1000000;
  int lMax = 0;
  int lfMin = 1000000;
  int lfMax = 0;
  int rfMin = 1000000;
  int rfMax = 0;
  int rMin = 1000000;
  int rMax = 0;
  steerRobot(pub,0,maxTurn);
  for(int i = 0; i < 100; ++i) // magic constant; hopefully this will be enough to pick up numbers.
  {
    while(!newInfo) { }
    newInfo = false;
    lMin = min(lMin,lSensorVal);
    lMax = max(lMax,lSensorVal);
    lfMin = min(lfMin,lfSensorVal);
    lfMax = max(lfMax,lfSensorVal);
    rfMin = min(rfMin,rfSensorVal);
    rfMax = max(rfMax,rfSensorVal);
    rMin = min(rMin,rSensorVal);
    rMax = max(rMax,rSensorVal);  
  }
  steerRobot(pub,0,0); // stop!
  ROS_INFO("Calibration complete.  Steer robot so that front\n  left sensor is on line and front right is not, and press enter to continue.");

  std::cin.sync();
  std::cin.get();

    // get line type; set thresholds.
    //  - thresholds are overlapping, so we don't have the "back and forth" problem
  while(!newInfo) { }

  ROS_INFO("Assuming robot's front left sensor is on the line and its right sensor is off the line... go!");

  bool lineIsBright = (lfSensorVal > rfSensorVal);

  //ROS_INFO("sensors read: left was %s,", lfSensorVal);
  //ROS_INFO("right was %s", rfSensorVal);

  float lThresholdBrightToDark = dtrace("lthreshB->D", lMin + 0.4f*(lMax-lMin));
  float lThresholdDarkToBright = dtrace("lthreshD->B", lMin + 0.6f*(lMax-lMin));
  float lfThresholdBrightToDark = dtrace("lfthreshB->D", lfMin + 0.4f*(lfMax-lfMin));
  float lfThresholdDarkToBright = dtrace("lfthreshD->B", lfMin + 0.6f*(lfMax-lfMin));
  float rfThresholdBrightToDark = dtrace("rfthreshB->D", rfMin + 0.4f*(rfMax-rfMin));
  float rfThresholdDarkToBright = dtrace("rfthreshD->B", rfMin + 0.6f*(rfMax-rfMin));
  float rThresholdBrightToDark = dtrace("rthreshB->D", rMin + 0.4f*(rMax-rMin));
  float rThresholdDarkToBright = dtrace("rthreshD->B", rMin + 0.6f*(rMax-rMin));

  // State variables
  bool wasBumped = false; // during last iteration, at least one bump sensor was on
  float unBumpedSpeed = 0;
  float unBumpedTurn = 0;
  float speed = 0; // no speed to start
  float turn = maxTurn; // go CCW to start
  // (one-sensor only)
  bool wasOnLine = true; // during last iteration, robot was on the line
  // (two-sensor only)
  bool wasOnLineLeft = true; // if we were hitting the line with the left sensor
  bool wasOnLineRight = false; // if we were hitting the line with the right sensor 

  // Go!
  steerRobot(pub,speed,turn);
  // loop between getting data and pushing out a new action.  The robot will:
  //  - twist rightwards ("twistRight") if on the line, in an effort to get off of it
  //  - push the forward, turning leftward, ("pushLeft") if off the line,
  //      in an effort to get back on it

  ros::Rate loop_rate(40);
  while(ros::ok())
  {
    while(!newInfo) { }
    newInfo = false;
    if(bump)
    {
      if(!wasBumped)
      {
        // Boston driver response
        ROS_INFO("Hey, watch where you're going!");
        unBumpedSpeed = dtrace("speed",speed);
        unBumpedTurn = dtrace("turn",turn);
      }
      wasBumped = true;
      // halt!
      speed = 0;
      turn = 0;
    }
    else if(wasBumped)
    {
      ROS_INFO("Outta my way!");
      wasBumped = false;
      speed = unBumpedSpeed;
      turn = unBumpedTurn;
    }
    else //not bump
    {
      if(false) // one-sensor following: front left sensor (CONSTANT)
      {          
        if(wasOnLine)
        {
          if (((lineIsBright && (lfSensorVal < lfThresholdBrightToDark)) ||
             ((!lineIsBright) && (lfSensorVal > lfThresholdDarkToBright))))
          {
            ROS_INFO("Left the line!");
            wasOnLine = false;
            speed = maxSpeed;
            turn = -maxTurn;
          }
          else // haven't left the line yet; slow down more
          {
            speed = speed/speedDecayRate;
          }
        }
        else // not wasOnLine
        {  
          if (((lineIsBright && (lfSensorVal > lfThresholdDarkToBright)) ||
          ((!lineIsBright) && (lfSensorVal < lfThresholdBrightToDark))))
          {
            ROS_INFO("Got back on the line!");
            wasOnLine = true;
            speed = maxSpeed;
            turn = maxTurn;
          }
          else // haven't gotten back on the line yet; slow down more
          {
            speed /= speedDecayRate;
          }
        }
      }            
      else // two-sensor following: far left and right sensors
      {
                if(wasOnLineLeft)
                {
                    if (((lineIsBright && (lfSensorVal < lfThresholdBrightToDark)) ||
                        ((!lineIsBright) && (lfSensorVal > lfThresholdDarkToBright))))
                    {
                      ROS_INFO("Left the line (left sensor)!");
                      wasOnLineLeft = false;
                      speed = maxSpeed;
                      turn = 0;
                    }
                    else // haven't left the line yet; slow down more
                    {
                        speed = speed/speedDecayRate;
                    }
                 }
                  if (wasOnLineRight)
                  {
                    if (((lineIsBright && (rfSensorVal < rfThresholdBrightToDark)) ||
                        ((!lineIsBright) && (rfSensorVal > rfThresholdDarkToBright))))
                    {
                        ROS_INFO("Left the line! (right sensor)");
                        wasOnLineRight = false;
                        speed = maxSpeed;
                        turn = 0;
                    }
                    else // haven't left the line yet; slow down more
                    {
                        speed = speed/speedDecayRate;
                    }
                }
                else // not wasOnLine{Left,Right}
                {
                    if (((lineIsBright && (lfSensorVal > lfThresholdDarkToBright)) ||
                        ((!lineIsBright) && (lfSensorVal < lfThresholdBrightToDark))))
                    {
                        ROS_INFO("Got back on the line (left sensor)!");
                        wasOnLineLeft = true;
                        speed = 0;
                        turn = maxTurn;
                    }
                    else if (((lineIsBright && (rfSensorVal > rfThresholdDarkToBright)) ||
                            ((!lineIsBright) && (rfSensorVal < rfThresholdBrightToDark))))
                    {
                        ROS_INFO("Got back on the line (right sensor)!");
                        wasOnLineRight = true;
                        speed = 0;
                        turn = -maxTurn;
                    }
                    else // haven't gotten back on the line yet; keep going!
                    {
                        speed = maxSpeed;
                        turn = 0;
                    }
                }
       }
    }
    steerRobot(pub,speed,turn);

    ros::spin();
    loop_rate.sleep();
  }
  // Stop!
  steerRobot(pub,0,0);

  return 0;
}
