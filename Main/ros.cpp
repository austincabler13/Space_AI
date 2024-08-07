#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        cv::Mat image = cv_bridge::toCvCopy(msg, "bgr8")->image;
        // Process image for obstacle detection
        // Use OpenCV to detect obstacles
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "obstacle_detection");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("camera/image", 1, imageCallback);
    ros::spin();
    return 0;
}
