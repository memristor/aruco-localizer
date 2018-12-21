#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    VideoCapture cap(-1);     // get 'any' cam
    while( cap.isOpened() )   // check if we succeeded
    {
        Mat frame;
        if ( ! cap.read(frame) )
            break;

        threshold(frame, frame, 50, 255, 1);
        imshow("Webcam",frame);
        int k = waitKey(33);
        if ( k==27 )
            break;
    }
    return 0;
}