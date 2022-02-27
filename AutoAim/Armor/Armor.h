//
// Created by Shangzheng Ji on 11/13/21.
//

#ifndef RM_ARMOR_H
#define RM_ARMOR_H

#include <opencv2/opencv.hpp>

class LED_bar {
public:
    LED_bar() = default;

    explicit LED_bar(const cv::RotatedRect &rect) {
        this->rotatedRect = rect;

        if(rect.size.width < rect.size.height){
            this->angle = rect.angle+180;
        }else {
            this->angle = rect.angle+90;
        }
        /**
        if (rect.size.width < rect.size.height) {
             this->angle = rect.angle+90;
        }else{
            this->angle = rect.angle;
        }
         **/
    }

    bool matched = false;
    size_t matched_index = -1;
    cv::RotatedRect rotatedRect;
    float angle = -1;
private:
};

class Armor {
public:
    Armor();

    Armor(const LED_bar &left, const LED_bar &right);

    void draw_Armor(cv::Mat &image, cv::Point2f roi_offset, bool drawCenter) const;

    bool match_LEDs(const cv::Mat &img);

    bool Armor_constraints();

    int get_average_intensity(const cv::Mat &img);

    LED_bar left;
    LED_bar right;
    float error_angle;
    cv::Point2i center;
    cv::RotatedRect rect;
    bool is_small_armor;
    // int average_intensity = -1;



private:
    double Euclidean_distance() const {
        return std::sqrt(pow(left.rotatedRect.center.x - right.rotatedRect.center.x, 2) +
                         pow(left.rotatedRect.center.y - right.rotatedRect.center.y, 2));
    }
    double center_height_difference() const {
        return fabs(left.rotatedRect.center.y - right.rotatedRect.center.y);
    }



    double height_ratio() const {
        if(left.rotatedRect.size.height >= right.rotatedRect.size.height) {
            return left.rotatedRect.size.height/ right.rotatedRect.size.height;
        } else {
            return right.rotatedRect.size.height/ left.rotatedRect.size.height;
        }
    }

    double width_two_center() const{
        return fabs(left.rotatedRect.center.x - right.rotatedRect.center.x);
    }


    double height_width_ratio() const {
        //return rect.width / rect.height;
        if (rect.size.width < rect.size.height)
            return rect.size.width / rect.size.height;
        else
            return rect.size.height / rect.size.width;
    }

};


#endif //RM_ARMOR_H
