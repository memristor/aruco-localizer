#include <string>
#include <sstream>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

namespace markers {

    #define SEPARATOR std::string("/")
    #define FOLDER_MARKERS std::string("markers")
    #define FOLDER_MARKER_IMAGES std::string("images")

    #define MARKER_IMAGE_SIZE 512
    #define MARKER_BORDER_SIZE 1
    #define MARKER_IMAGE_TYPE std::string(".png")

    void generateImages(unsigned number) {

        std::filesystem::remove_all(FOLDER_MARKERS + SEPARATOR + FOLDER_MARKER_IMAGES);
        std::filesystem::create_directories(FOLDER_MARKERS + SEPARATOR + FOLDER_MARKER_IMAGES);

        std::cout << FOLDER_MARKERS + SEPARATOR + FOLDER_MARKER_IMAGES + SEPARATOR << std::endl;

        cv::Mat markerImage;
        cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);

        for (auto i = 0; i < number; ++i) {
            std::stringstream fileName;
            fileName << FOLDER_MARKERS << SEPARATOR << FOLDER_MARKER_IMAGES << SEPARATOR << i << MARKER_IMAGE_TYPE;
            dictionary.cv::aruco::Dictionary::drawMarker(i, MARKER_IMAGE_SIZE, markerImage, MARKER_BORDER_SIZE);
            cv::imwrite(fileName.str(), markerImage);
        }

    }

}
