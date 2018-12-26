#include <string>
#include <sstream>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#define FOLDER_MARKERS std::string("markers/")
#define FOLDER_MARKER_IMAGES std::string("images/")

#define MARKER_IMAGE_SIZE 512
#define MARKER_IMAGE_TYPE std::string(".png")

namespace markers {

    void generateImages(unsigned number) {

        std::filesystem::remove_all(FOLDER_MARKERS + FOLDER_MARKER_IMAGES);
        std::filesystem::create_directories(FOLDER_MARKERS + FOLDER_MARKER_IMAGES);

        cv::Mat markerImage;
        cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);

        for (auto i = 0; i < number; ++i) {
            std::stringstream fileName;
            fileName << FOLDER_MARKERS << FOLDER_MARKER_IMAGES << i << MARKER_IMAGE_TYPE;
            dictionary.cv::aruco::Dictionary::drawMarker(i, MARKER_IMAGE_SIZE, markerImage, 1);
            cv::imwrite(fileName.str(), markerImage);
        }

    }

}
