//
// Created by Shangzheng Ji on 11/13/21.
//

#ifndef RM_DETECTOR_H
#define RM_DETECTOR_H


#include <stdio.h>
#include <stdarg.h>
#include <opencv2/opencv.hpp>

#include <vector>

using namespace cv;
using namespace std;

class Detector{
public:
    Detector();
    Point2f Detect(Mat &input);
    int binary_thresh;
    int morph_size;
    int blur_size;
    int rectAngle;
    bool is_small_armor=false;

private:
    bool armorFound;
    vector<int> armorBounds;
    vector<int> RegionOfInterest();
    void detector_debug(Mat &raw, Mat &thresh, Mat &binary, Mat &dilated, bool show_raw = false, bool show_thresh = false,
            bool show_binary = false, bool show_dilated = false);
};
#endif //RM_DETECTOR_H
