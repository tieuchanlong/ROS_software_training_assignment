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


	ros::Publisher velocity_publisher = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	ros::Publisher angle_publisher = n.advertise<turtlesim::Pose>("turtle1/pose", 1000);
	ros::Rate loop_rate(1);

	int count = 0;
	srand(time(NULL));
	turtlesim::Pose vel_msgs;
	geometry_msgs::Twist ang_msgs; 

	double t0 = ros::Time::now().toSec();
	double angle = atan(20/5) + 3.1415;
	double dist = sqrt(20*20 + 5*5);

	while(ros::ok())
	{
		//vel_msgs.orientation.x = 5;
		//vel_msgs.orientation.y = 20;
		//vel_msgs.orientation.z = 2.09;

		ang_msgs.angular.z = 1;

		double t1 = ros::Time::now().toSec();
		double current_angle = t1 - t0;

		ROS_INFO("Random positon linear: %.2f", vel_msgs.theta);

		if (current_angle >= angle)
		{
			ROS_INFO("Turtle reaches angle!!");
			break;
		}		

		velocity_publisher.publish(ang_msgs);
		angle_publisher.publish(vel_msgs);
		ros::spinOnce();
		loop_rate.sleep();
		count++;
	}

	t0 = ros::Time::now().toSec();

	while(ros::ok())
        {
                ang_msgs.linear.x = 1;
		ang_msgs.angular.z = 0;

                double t1 = ros::Time::now().toSec();
                double current_dist = t1 - t0;

                if (current_dist >= dist)
                {
                        ROS_INFO("Turtle reaches destination!!");
                        break;
                }

                velocity_publisher.publish(ang_msgs);
                angle_publisher.publish(vel_msgs);
                ros::spinOnce();
                loop_rate.sleep();
                count++;
        }


	return 0;
}
