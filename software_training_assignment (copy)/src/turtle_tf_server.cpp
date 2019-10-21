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
	turtlesim::Spawn srv1;

	srv.request.x = 5;
	srv.request.y = 5;
	srv.request.theta = 0;
	srv.request.name = "stationary_turtle";
	
	srv1.request.x = 25;
	srv1.request.y = 10;
	srv1.request.theta = 0;
	srv1.request.name = "moving_turtle";
	
	if (stationary_turtle.call(srv))
	{
		ROS_INFO("Turtle is spawned!");
	}
	else ROS_INFO("The turtle has not been spawned!");

	stationary_turtle.call(srv1);
	
	//ROS_INFO("The turtle name and pos is: %f %f %s", srv.request.x, srv.request.y, srv.request.name.c_str());

	ros::spinOnce();


	return 0;
}
