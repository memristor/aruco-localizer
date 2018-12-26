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
    
    cv::VideoCapture inputVideo;
    inputVideo.open(0);
    inputVideo.set(CV_CAP_PROP_FRAME_WIDTH, 2000);
    inputVideo.set(CV_CAP_PROP_FRAME_HEIGHT, 2000);
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

        cv::Size patternsize(9, 7); //interior number of corners
        // cv::Mat gray = image; 
        std::vector<cv::Point2f> _corners; //this will be filled by the detected corners
        //CALIB_CB_FAST_CHECK saves a lot of time on images
        //that do not contain any chessboard corners
        // bool patternfound = findChessboardCorners(gray, patternsize, corners,
        //         cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
        //         + cv::CALIB_CB_FAST_CHECK);
        // if(patternfound)
        // cornerSubPix(gray, _corners, cv::Size(11, 11), cv::Size(-1, -1),
        //     cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            // drawChessboardCorners(imageCopy, patternsize, cv::Mat(_corners), patternfound);

        bool found = findChessboardCorners(image, patternsize, _corners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
                + cv::CALIB_CB_FAST_CHECK);
        if(found)
        {
            cv::putText(imageCopy, "DETECTED", cv::Point(20, 20), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0,255,0), 2.0);
            drawChessboardCorners(imageCopy, patternsize, cv::Mat(_corners), found);
        }


        // for (auto& c : corners)
        //     std::cout << c << std::endl;

        cv::imshow("out", imageCopy); 
        char key = (char) cv::waitKey(20); 
        if (key == 27)
            break; 
    }

    return 0;
}