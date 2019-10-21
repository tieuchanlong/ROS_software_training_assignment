#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "software_training_assignment/TurtleDistance.h"
#include "turtlesim/Spawn.h"

#include <sstream>
#include <math.h>

using software_training_assignment::TurtleDistance;

void poseCallback(const turtlesim::Pose::ConstPtr& pose_message,turtlesim::Pose *pos_data)
{
	pos_data->x = pose_message->x;
	pos_data->y = pose_message->y;
	//ROS_INFO("Initial pos: %.2f", pose_message->x);
}

void PubPosition(turtlesim::Pose turtle1, turtlesim::Pose turtle2, ros::Publisher dist_pub)
{
	TurtleDistance result;
	result.x_dist = abs(turtle1.x - turtle2.x);
	result.y_dist = abs(turtle1.y - turtle2.y);
	result.dist = sqrt(pow(abs(turtle1.x - turtle2.x),2) + pow(abs(turtle1.y - turtle2.y),2));
	ROS_INFO("x: %.2f y: %.2f dist: %.2f", result.x_dist, result.y_dist, result.dist);
	dist_pub.publish(result);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "turtle_tf_distance");
	ros::NodeHandle n;

	ros::Rate loop_rate(10);

	int count = 0;
	srand(time(NULL));
	turtlesim::Pose stationary_msgs;
	turtlesim::Pose moving_msgs;
	
	ros::Subscriber stationary_turtle_subscriber = n.subscribe<turtlesim::Pose>("stationary_turtle/pose", 100, boost::bind(&poseCallback, _1, &stationary_msgs));
        ros::Subscriber moving_turtle_subscriber = n.subscribe<turtlesim::Pose>("moving_turtle/pose", 100, boost::bind(&poseCallback, _1, &moving_msgs)); 

	ros::Publisher dist_publisher = n.advertise<software_training_assignment::TurtleDistance>("turtle_distance", 10);

	while (ros::ok())
	{
		PubPosition(stationary_msgs, moving_msgs, dist_publisher);
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	ros::spin();
	return 0;
}
