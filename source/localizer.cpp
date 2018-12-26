#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

#include "markers.cpp"

int main(int argc, char** argv)
{

    if (argc > 1) {
        if (argv[1] == std::string("generate")) {
            markers::generateImages(atoi(argv[2]));
        }
        if (argv[1] == std::string("detect")) {
            std::cout << "DETECTING" << std::endl;
        }
    }
    
    cv::VideoCapture inputVideo; inputVideo.open(0);
    // cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
    while (inputVideo.grab()) { 
        cv::Mat image, imageCopy; 
        inputVideo.retrieve(image); 
        image.copyTo(imageCopy);
    
        cv::Ptr<cv::aruco::DetectorParameters> parameters;
        cv::Ptr<cv::aruco::Dictionary> dictionary=cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);

        std::vector<int> ids; 
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        if (ids.size() > 0) 
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids, cv::Scalar(255, 50, 200));

        // for (auto& c : corners)
        //     std::cout << c << std::endl;

        cv::imshow("out", imageCopy); 
        char key = (char) cv::waitKey(20); 
        if (key == 27)
            break; 
    }

    return 0;
}