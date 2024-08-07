#include <opencv2/opencv.hpp>

void detectObstacles(cv::Mat& frame) {
    cv::Mat gray, edges;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, edges, cv::Size(5, 5), 1.5);
    cv::Canny(edges, edges, 50, 150);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
        cv::Rect boundingBox = cv::boundingRect(contour);
        if (cv::contourArea(contour) > 100) {
            cv::rectangle(frame, boundingBox, cv::Scalar(0, 255, 0), 2);
        }
    }
}
