#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "sensor_msgs/Joy.h"
#include "turtlesim/Spawn.h"
#include <sstream>


int main(int argc, char **argv)
{
	ros::init(argc, argv, "turtle_tf_server");
	ros::NodeHandle n;

	
	ros::ServiceClient stationary_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
	turtlesim::Spawn srv;
	
	
	if (stationary_turtle.call(srv)) srv.response.name = "spawn_turtle";
	else ROS_INFO("The turtle has not been spawned!");
	
	ROS_INFO("The turtle name and pos is: %f %f %s", srv.request.x, srv.request.y, srv.request.name.c_str());

	ros::spin();


	return 0;
}
