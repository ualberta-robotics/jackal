# Mark location of self so that robot_upstart knows where to find the setup file.
export ROBOT_SETUP=/etc/ros/setup.bash

# Setup robot upstart jobs to use the IP from the network bridge.
# export ROBOT_NETWORK=br0

# Insert extra platform-level environment variables here. The six hashes below are a marker
# for scripts to insert to this file.
######

# Laser Environment Variables
export JACKAL_LASER=1
export JACKAL_LASER_MODEL=ust10

# Pass through to the main ROS workspace of the system.
source /opt/ros/noetic/setup.bash
