//
// Created by Shangzheng Ji on 11/13/21.
//

#include "../Armor/Armor.h"
#include "Detector.h"
#include "math.h"
#define BLUE;


void ShowManyImages(string title, int nArgs, ...);

Detector::Detector() {
    armorFound = false;
    armorBounds = {320, 240, 320, 240}; // center coordinate of 640 x 480
    binary_thresh = 0;
    morph_size = 7;
    blur_size = 7;
    rectAngle = 0;
}

/*
Detector::Detector(){
    armorFound = false; //initialize to false
    vector<int> armorBounds{320, 240, 320, 240}; // center point of 640 x 480
}
 */


//TODO: implement ROI function
/*
 * Description: After the detection of desired armor from Detect, ROI instantly zooms in the frame to the region of
 * the desired armor; zooms out when desired armor is out of ROI, until it finds the next desired armor.
 *
 * @return topLeftX, topLeftY, bottomRightX, bottomRightY
 */


//static bool armorFound = false; //initialize to false
//static vector<int> armorBounds{}; // center point of 640 x 480
//static int max_x = 640;
//static int max_y = 480;

vector<int> Detector::RegionOfInterest(){
    int increment = 10;
    int offset = 10;

    //return ROI with offset when the armor is detected
    if(armorFound){
        //add offset to TopLeftX and TopLeftY
        for(int i = 0; i <= 1; i++){
            if((armorBounds[i] - offset) >= 0) {
                armorBounds[i] -= offset;
            }
            else{ //extend the bound to its max limit
                armorBounds[i] -= armorBounds[i] - 0;
            }
        }
        //add offset to BottomRightX
        if((armorBounds[2] + offset) <= 640) {
            armorBounds[2] += offset;
        }
        else{
            armorBounds[2] += 640 - armorBounds[2];
        }

        //add offset to BottomRightY
        if((armorBounds[3] + offset) <= 480){
            armorBounds[3] += offset;
        }
        else{
            armorBounds[3] += 480 - armorBounds[3];
        }

        //return original region coordinates with offset
        return armorBounds;
    }

        //when armor is not detected
    else{
        for(int i = 0; i <= 1; i++){
            if((armorBounds[i] - increment) >= 0) {
                armorBounds[i] -= increment;
            }
            else{
                armorBounds[i] -= armorBounds[i] - 0;
            }
        }
        if((armorBounds[2] + increment) <= 640) {
            armorBounds[2] += increment;
        }
        else{
            armorBounds[2] += 640 - armorBounds[2];
        }

        if((armorBounds[3] + increment) <= 480){
            armorBounds[3] += increment;
        }
        else{
            armorBounds[3] += 480 - armorBounds[3];
        }

        /*add offset to ROI*/
        //add offset to TopLeftX and TopLeftY
        for(int i = 0; i <= 1; i++){
            if((armorBounds[i] - offset) >= 0) {
                armorBounds[i] -= offset;
            }
            else{ //extend the bound to its max limit
                armorBounds[i] -= armorBounds[i] - 0;
            }
        }
        //add offset to BottomRightX
        if((armorBounds[2] + offset) <= 640) {
            armorBounds[2] += offset;
        }
        else{
            armorBounds[2] += 640 - armorBounds[2];
        }

        //add offset to BottomRightY
        if((armorBounds[3] + offset) <= 480){
            armorBounds[3] += offset;
        }
        else{
            armorBounds[3] += 480 - armorBounds[3];
        }

        //return original region coordinates with offset
        return armorBounds;
    }
}

Point2f Detector::Detect(Mat &input) {
    //cout << "111111" << endl;
    Mat raw, blurred, gray, binary, dilated, bgr[3], contour;
    raw  = input.clone();
    //RotatedRect rRect = RotatedRect(Point2f(320, 240), Size2f(100, 500), rectAngle);
    //Point2f vertices[4];
    //rRect.points(vertices);
    //for (int i = 0 ; i < 4; i++) {
     //   line(raw, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));
    //}
    //Rect brect = rRect.boundingRect();
    //rectangle(raw, brect, Scalar(255,0,0));
    //imshow("Rect", raw);
    //raw = input.clone();
    //contour  = raw.clone();
    //resize(raw, raw, Size(640,480));
    //vector<int> rois = RegionOfInterest();
    //raw = raw(Range(rois[1],rois[3]), Range(rois[0], rois[2]));
    //imshow("Input", input);
    //GaussianBlur(raw, blurred, Size(blur_size, blur_size), 0);
    //imshow("img", blurred);
    split(raw, bgr);


   vector<vector<Point>> contours;
   vector<Vec4i> hierarchy;


#ifdef BLUE
   gray = bgr[0] - bgr[2];
#else
   gray = bgr[2] - bgr[0];
#endif

    threshold(gray, binary, 127, 255, THRESH_BINARY);
    morphologyEx(binary ,dilated, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(morph_size, morph_size)));
    findContours(dilated, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
    //cout << contours.size() << endl;
    //drawContours(contour, contours, -1, Scalar(0,0,255), 3, FILLED);
    //imshow("Contours", contour);

    //detector_debug (raw, gray, binary, dilated, false, true, true, false);



    cv::Point2f offset= {0,0};
    vector<LED_bar> LEDs;

    for (int i = 0; i < contours.size(); i++){
        LED_bar led = LED_bar(minAreaRect(contours[i]));
        cout << "Led angle: " << led.angle << std::endl;
        LEDs.push_back(led);

    }

   for (int i = 0; i < LEDs.size(); i++) {
       Point2f vertices[4];
       LEDs[i].rotatedRect.points(vertices);
       for (int i = 0; i < 4; i++)
           line(raw, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
       Rect brect = LEDs[i].rotatedRect.boundingRect();
       rectangle(raw, brect, Scalar(255, 0, 0), 2);

   }
    //imshow("rectangles", raw);


    vector<Armor> armors;
    for (int i = 0; i < LEDs.size(); i++){
        //cout << LEDs.size() << endl;
        for (int j = i + 1; j < LEDs.size(); j++) {
            Armor armor = Armor(LEDs[i], LEDs[j]);
           cout << LEDs.size() << endl;
            if(armor.match_LEDs(gray)) {
                armors.push_back(armor);
                //std::cout << "Left Bar: " << armor.left.angle << std::endl;
                //std::cout << "Right Bar: " << armor.right.angle << std::endl;
                armor.draw_Armor(raw,offset,false);

            }
        }
    }

   imshow("Armors", raw);

    double closest_to_center = DBL_MAX;
    double distance_to_center = 0;
    Armor final_armor;

    armorFound = false;
    for(Armor valid_armor: armors){
        distance_to_center = sqrt(pow(320 - valid_armor.center.x, 2) + pow(240 - valid_armor.center.y, 2));
         if (distance_to_center < closest_to_center) {
             closest_to_center = distance_to_center;
             final_armor = valid_armor;
             armorFound = true;
             armorBounds = {valid_armor.center.x - valid_armor.rect.size.width / 2,
                            valid_armor.center.y - valid_armor.rect.size.height / 2,
                            valid_armor.center.x + valid_armor.rect.size.width / 2,
                            valid_armor.center.y + valid_armor.rect.size.height / 2};

         }
    }

    //final_armor.draw_Armor(raw, offset, true);
    //imshow("Target", raw);


}

void Detector::detector_debug (Mat &raw, Mat &gray, Mat &binary, Mat &dilated, bool show_raw , bool show_gray,
                    bool show_binary, bool show_dilated )
{
    if(show_raw) imshow("raw", raw);
    if(show_gray) imshow("gray", gray);
    if(show_binary) imshow("binary", binary);
    if(show_dilated) imshow("dilated", dilated);
}



