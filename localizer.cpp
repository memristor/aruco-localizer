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
    }
    
    return 0;
}