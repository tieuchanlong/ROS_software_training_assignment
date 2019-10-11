#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <software_training_assignment/MoveTurtle.h>

class MoveTurtleAction
{
	protected:
		ros::NodeHandle nh_;
		actionlib::SimpleActionServer<software_training_assignment::MoveTurtle> as_;
		
		std::string action_name_;

		software_training_assignment::MoveTurtleFeedback feedback_;
		software_training_assignment::MoveTurtleResult result_;

	public:
		MoveTurtleAction(std::string name): as_(nh_, name, boost::bind(&MoveTurtleAction::executeCB, this, _1), false), action_name_(name)
		{
			as_.start();
		}

		~MoveTurtleAction(void)
		{
		}
		
		void executeCB(const actionlib_tutorials::MoveTurtleGoalConstPtr &goal)
		{
			ros::Rate r(1);
			bool success = true;
			
			feedback_.distance_to_goal
			
			// publish info to the console for the user
   			 ROS_INFO("%s: Executing, creating turtle movement of order %i with seed %.2f", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.distance_to_goal);
			
			for (int i = 1;i<=goal->order; i++)
			{
				// check that preempt has not been requested by the client
     				 if (as_.isPreemptRequested() || !ros::ok())
     				 {
       					 ROS_INFO("%s: Preempted", action_name_.c_str());
       					 // set the action state to preempted
       					 as_.setPreempted();
       					 success = false;
       					 break;
     				 }

				as_.publishFeedback(feedback_);
     				 // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
     				 r.sleep();
			}
		}
}
