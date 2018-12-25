#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

void createMarkers(unsigned number) {

    std::filesystem::remove_all("markers/images");
    std::filesystem::create_directories("markers/images");

    cv::Mat markerImage;
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
    char fileName[256];

    for (auto i = 0; i < number; ++i) {
        std::snprintf(fileName, 256, "markers/images/%i.png", i);
        dictionary.cv::aruco::Dictionary::drawMarker(i, 512, markerImage, 1);
        cv::imwrite(fileName, markerImage);
    }

}

int main(int argc, char** argv)
{
    // VideoCapture cap(-1);     // get 'any' cam
    // while( cap.isOpened() )   // check if we succeeded
    // {
    //     Mat frame;
    //     if ( ! cap.read(frame) )
    //         break;

    //     Mat frame1, frame2, frame3, frame4;

    //     cvtColor(frame, frame1, cv::COLOR_BGR2HSV);

    //     Mat planes[3];

    //     split(frame1, planes);

    //     inRange(planes[0], 20, 40, frame2);

    //     inRange(planes[2], 150, 255, frame3);

    //     Mat element = getStructuringElement( 0,
    //                                    Size( 20, 20 ),
    //                                    Point( 1, 1 ) );

    //     erode(frame2 & frame3, frame4, element);

    //     std::vector<std::vector<cv::Point> > contours;
    //     cv::Mat contourOutput = frame4.clone();
    //     cv::findContours( contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );

    //     //Draw the contours
    //     cv::Mat contourImage(frame4.size(), CV_8UC3, cv::Scalar(0,0,0));
    //     cv::Scalar colors[3];
    //     colors[0] = cv::Scalar(255, 0, 0);
    //     colors[1] = cv::Scalar(0, 255, 0);
    //     colors[2] = cv::Scalar(0, 0, 255);
    //     for (size_t idx = 0; idx < contours.size(); idx++) {
    //         cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
    //     }


    //     imshow("Webcam", frame);
    //     imshow("Filter", contourImage);
    //     int k = waitKey(33);
    //     if ( k==27 )
    //         break;
    // }

    if (argc > 1) {
        if (argv[1] == std::string("generate")) {
            createMarkers(atoi(argv[2]));
        }
    }
    
    return 0;
}