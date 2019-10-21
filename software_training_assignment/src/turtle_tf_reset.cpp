#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "sensor_msgs/Joy.h"
#include "std_srvs/Empty.h"
#include <sstream>


int main(int argc, char **argv)
{
	ros::init(argc, argv, "turtle_tf_reset");
	ros::NodeHandle n;

	
	ros::ServiceClient moving_turtle = n.serviceClient<std_srvs::Empty>("reset");
	std_srvs::Empty srv;
	
	if (moving_turtle.call(srv))
	{
		ROS_INFO("Moving turtle is reset!");
	}
	else ROS_INFO("The moving turtle has not been reset!");

	
	//ROS_INFO("The turtle name and pos is: %f %f %s", srv.request.x, srv.request.y, srv.request.name.c_str());

	ros::spinOnce();


	return 0;
}
