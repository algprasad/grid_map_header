#include <iostream>
#include "ros/ros.h"
#include <grid_map_msgs/GridMap.h>
#include <grid_map_header/GridMapWithHeader.h>

grid_map_header::GridMapWithHeader grid_map_with_header_msg;
ros::Publisher pub_elevation_map_with_header;
static unsigned int sequence = 1;
void gridMapCallback(const grid_map_msgs::GridMapConstPtr& grid_map_msg){
    grid_map_with_header_msg.header.seq = sequence++;
    grid_map_with_header_msg.header.stamp = ros::Time::now();

    grid_map_with_header_msg.grid_map = *grid_map_msg;

}

int main(int argc, char **argv){
	ros::init(argc, argv, "grid_map_header");
	ros::NodeHandle nh;

	// Publisher and Subsriber stuff
	pub_elevation_map_with_header = nh.advertise<grid_map_header::GridMapWithHeader>("hippocampus/elevation_map", 1000);

	ros::Subscriber sub = nh.subscribe<grid_map_msgs::GridMap>("elevation_mapping/elevation_map", 1000, gridMapCallback);
	ros::Rate rate(20);

	while (ros::ok()){
        pub_elevation_map_with_header.publish(grid_map_with_header_msg);
        ros::spinOnce();
        rate.sleep();
	}


	return 0;


}
