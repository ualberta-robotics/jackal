# Configuration Files for the Jackal
The files in this folder are files used for configuration/ROS startup on the jackal to start the environment properly.

- accessories.launch: file goes in /etc/ros/noetic/ros.d, this is a modified version that sets up the hokuyo urg laser to use the serial device for launch instead of an IP
- setup.bash: file goes in /etc/ros, sets the environment variables for the jackal to start the laser scanner on startup by default.