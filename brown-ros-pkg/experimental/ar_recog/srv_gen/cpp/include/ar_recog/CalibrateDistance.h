/* Auto-generated by genmsg_cpp for file /home/ulrich/ros_workspace/brown-ros-pkg/experimental/ar_recog/srv/CalibrateDistance.srv */
#ifndef AR_RECOG_SERVICE_CALIBRATEDISTANCE_H
#define AR_RECOG_SERVICE_CALIBRATEDISTANCE_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "ros/service_traits.h"




namespace ar_recog
{
template <class ContainerAllocator>
struct CalibrateDistanceRequest_ {
  typedef CalibrateDistanceRequest_<ContainerAllocator> Type;

  CalibrateDistanceRequest_()
  : dist(0)
  {
  }

  CalibrateDistanceRequest_(const ContainerAllocator& _alloc)
  : dist(0)
  {
  }

  typedef int32_t _dist_type;
  int32_t dist;


private:
  static const char* __s_getDataType_() { return "ar_recog/CalibrateDistanceRequest"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "e2c1055fbb10edc20f225fe99e18b131"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getServerMD5Sum_() { return "b825ddadc18a94e1aff9d418f4e6cfee"; }
public:
  ROS_DEPRECATED static const std::string __s_getServerMD5Sum() { return __s_getServerMD5Sum_(); }

  ROS_DEPRECATED const std::string __getServerMD5Sum() const { return __s_getServerMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "int32 dist\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, dist);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, dist);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(dist);
    return size;
  }

  typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct CalibrateDistanceRequest
typedef  ::ar_recog::CalibrateDistanceRequest_<std::allocator<void> > CalibrateDistanceRequest;

typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceRequest> CalibrateDistanceRequestPtr;
typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceRequest const> CalibrateDistanceRequestConstPtr;


template <class ContainerAllocator>
struct CalibrateDistanceResponse_ {
  typedef CalibrateDistanceResponse_<ContainerAllocator> Type;

  CalibrateDistanceResponse_()
  : aov(0.0)
  {
  }

  CalibrateDistanceResponse_(const ContainerAllocator& _alloc)
  : aov(0.0)
  {
  }

  typedef double _aov_type;
  double aov;


private:
  static const char* __s_getDataType_() { return "ar_recog/CalibrateDistanceResponse"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "18a96d7cdd9686621c8186905b79ee25"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getServerMD5Sum_() { return "b825ddadc18a94e1aff9d418f4e6cfee"; }
public:
  ROS_DEPRECATED static const std::string __s_getServerMD5Sum() { return __s_getServerMD5Sum_(); }

  ROS_DEPRECATED const std::string __getServerMD5Sum() const { return __s_getServerMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "float64 aov\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, aov);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, aov);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(aov);
    return size;
  }

  typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct CalibrateDistanceResponse
typedef  ::ar_recog::CalibrateDistanceResponse_<std::allocator<void> > CalibrateDistanceResponse;

typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceResponse> CalibrateDistanceResponsePtr;
typedef boost::shared_ptr< ::ar_recog::CalibrateDistanceResponse const> CalibrateDistanceResponseConstPtr;

struct CalibrateDistance
{

typedef CalibrateDistanceRequest Request;
typedef CalibrateDistanceResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct CalibrateDistance
} // namespace ar_recog

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "e2c1055fbb10edc20f225fe99e18b131";
  }

  static const char* value(const  ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xe2c1055fbb10edc2ULL;
  static const uint64_t static_value2 = 0x0f225fe99e18b131ULL;
};

template<class ContainerAllocator>
struct DataType< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ar_recog/CalibrateDistanceRequest";
  }

  static const char* value(const  ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32 dist\n\
\n\
";
  }

  static const char* value(const  ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "18a96d7cdd9686621c8186905b79ee25";
  }

  static const char* value(const  ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x18a96d7cdd968662ULL;
  static const uint64_t static_value2 = 0x1c8186905b79ee25ULL;
};

template<class ContainerAllocator>
struct DataType< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ar_recog/CalibrateDistanceResponse";
  }

  static const char* value(const  ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 aov\n\
\n\
";
  }

  static const char* value(const  ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::ar_recog::CalibrateDistanceRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.dist);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct CalibrateDistanceRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::ar_recog::CalibrateDistanceResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.aov);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct CalibrateDistanceResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<ar_recog::CalibrateDistance> {
  static const char* value() 
  {
    return "b825ddadc18a94e1aff9d418f4e6cfee";
  }

  static const char* value(const ar_recog::CalibrateDistance&) { return value(); } 
};

template<>
struct DataType<ar_recog::CalibrateDistance> {
  static const char* value() 
  {
    return "ar_recog/CalibrateDistance";
  }

  static const char* value(const ar_recog::CalibrateDistance&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "b825ddadc18a94e1aff9d418f4e6cfee";
  }

  static const char* value(const ar_recog::CalibrateDistanceRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<ar_recog::CalibrateDistanceRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ar_recog/CalibrateDistance";
  }

  static const char* value(const ar_recog::CalibrateDistanceRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "b825ddadc18a94e1aff9d418f4e6cfee";
  }

  static const char* value(const ar_recog::CalibrateDistanceResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<ar_recog::CalibrateDistanceResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ar_recog/CalibrateDistance";
  }

  static const char* value(const ar_recog::CalibrateDistanceResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // AR_RECOG_SERVICE_CALIBRATEDISTANCE_H

