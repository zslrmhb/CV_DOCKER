//#include <iostream>
//#include <Config/Config_reader.h>
//#include "Utility/utility.h"




//int main() {
//    Config_reader* configReader = new Config_reader();
//
//    configReader->parse();
//    std::cout << RT_utility::cameraMatrix_ <<std::endl;
//    std::cout << RT_utility::distCoeffs_ << std::endl;
//    delete configReader;
//    return 0;
//}


#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "AutoAim/Detector/Detector.h"
#include <chrono>
#include <stdio.h>
using namespace cv;
using namespace std;

void callBack(){

}



int main(int, char**)
{
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    //"v4l2src device=\"/dev/video0\" ! xvimagesink"
    //VideoCapture cap = VideoCapture(  "v4l2src device=/dev/video0 ! video/x-raw, width=(int)640, height=(int)480, format=MJPG !"  );
    VideoCapture cap;
   // ret_val, cap_for_exposure = cap.read();
    Detector det;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API

   // cap.set(CAP_PROP_EXPOSURE, 20);
    // open selected camera using selected API
    //cap.set(CAP_PROP_AUTO_EXPOSURE, 3);
   // cap.set(CAP_PROP_AUTO_EXPOSURE, 1);
    //cap.set(CAP_PROP_EXPOSURE, -13);
    //cap.set(CAP_PROP_BRIGHTNESS, 100);
    //cap.set(CAP_PROP_AUTO_EXPOSURE, 0.25);
    //cout << cap.get(CAP_PROP_EXPOSURE) << endl;
   // cap.set(CAP_PROP_SETTINGS , 1);
    //cap.set(CAP_PROP_FPS, 30);
    //cout << cap.get(CAP_PROP_AUTO_EXPOSURE) << endl;
    //cout<< cap.get(CAP_PROP_FPS) << endl;
    cap.open(deviceID, apiID);
    // check if we succeeded
    //const std::string videoStreamAddress = "http://100.112.209.172:8080/video";
    //cap.open(videoStreamAddress);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    namedWindow("Tracker", WINDOW_AUTOSIZE);
    /**
    string BinaryThresh = "Binary Threshold";
    string MorphSize = "Morph Size";
    string BlurSize = "Blur Size";
    createTrackbar(BinaryThresh, "Tracker", &det.binary_thresh, 255, 0);
    createTrackbar(MorphSize, "Tracker", &det.morph_size ,15, 0);
    createTrackbar(BlurSize, "Tracker", &det.blur_size ,15, 0);
     */

    //string angle = "Rect angle";
    //createTrackbar(angle, "Tracker", &det.rectAngle, 360, 0);



    auto start = chrono::system_clock::now();
    int num_frames = 0;
    for (;;)
    {

        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        num_frames++;
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        //imshow("Live", frame);
        det.Detect(frame);
        auto curr = chrono::system_clock::now();
        chrono::duration<double> delta = curr - start;
        if (delta.count() > 1) {
            cout << "FPS " << num_frames / delta.count() << endl;
            start = chrono::system_clock::now();
            num_frames = 0;
        }
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}



