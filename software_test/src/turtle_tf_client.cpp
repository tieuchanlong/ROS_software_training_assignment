#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_tf_client");
  if (argc != 3)
  {
    ROS_INFO("spawn turtle at X Y");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn srv;
  if (client.call(srv))
  {
    ROS_INFO("Spawn a turtle name: %s", srv.response.name.c_str());
  }
  else
  {
    ROS_ERROR("Failed to call spawn");
    return 1;
  }

  return 0;
}


