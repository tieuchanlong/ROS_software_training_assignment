#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "sensor_msgs/Joy.h"
#include "turtlesim/Spawn.h"
#include <sstream>
#include <math.h>


int main(int argc, char **argv)
{
	ros::init(argc, argv, "turtle_tf_server");
	ros::NodeHandle n;


	ros::Publisher stationary_turtle_publisher = n.advertise<turtlesim::Pose>("stationary_turtle/pose", 1000);
	ros::Publisher moving_turtle_publisher = n.advertise<turtlesim::Pose>("moving_turtle/pose", 1000);
	ros::Rate loop_rate(1);

	int count = 0;
	srand(time(NULL));
	turtlesim::Pose stationary_msgs;
	turtlesim::Pose moving_msgs;

	double t0 = ros::Time::now().toSec();

	while(ros::ok())
	{
		//vel_msgs.orientation.x = 5;
		//vel_msgs.orientation.y = 20;
		//vel_msg

		ROS_INFO("Stationary turtle position: %.2f %.2f", stationary_msgs.x, stationary_msgs.y);
		ROS_INFO("Moving turtle position: %.2f %.2f", moving_msgs.x, moving_msgs.y);
		
		stationary_turtle_publisher.publish(stationary_msgs);
		moving_turtle_publisher.publish(moving_msgs);

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
