//
// Created by Shangzheng Ji on 11/13/21.
//

#include "Armor.h"
using namespace cv;
Armor::Armor(){}

Armor::Armor(const LED_bar &left, const LED_bar &right) {
    this->left = left;
    this->right = right;
    error_angle = fabs(left.rotatedRect.angle - right.rotatedRect.angle);

    rect.size.width = abs(static_cast<int>(left.rotatedRect.center.x - right.rotatedRect.center.x));
    rect.size.height = static_cast<int>((left.rotatedRect.size.height + right.rotatedRect.size.height) / 2);
    center.x = static_cast<int>((left.rotatedRect.center.x + right.rotatedRect.center.x) / 2);
    center.y = static_cast<int>((left.rotatedRect.center.y + right.rotatedRect.center.y) / 2);
   // rect.x = center.x - rect.width / 3;
    //rect.y = center.y - rect.height / 3;
    rect.angle = left.angle;
    rect.center.x = center.x - rect.size.width / 2;
    rect.center.y = center.y - rect.size.height / 2;
    //rect.width *= 2 / 3;
   // rect.height *= 2 / 3;
    std::vector<cv::Point> shape;
    Point2f leftPoints[4];
    this->left.rotatedRect.points(leftPoints);
    Point2f rightPoints[4];
    this->right.rotatedRect.points(rightPoints);
    for (int i = 0; i < 4; i++) {
        shape.push_back(leftPoints[i]);
        shape.push_back(rightPoints[i]);
    }
    rect = cv::minAreaRect(shape);

}
/**
 *
 * @param img the input image
 * @return the intensity of the
 */
int Armor::get_average_intensity(const cv::Mat &img) {
    /**
    if (rect.width < 1 || rect.height < 1 || rect.x < 1 || rect.y < 1
        || rect.width + rect.x > img.cols || rect.height + rect.y > img.rows)
        return 255;
    Mat roi = img(Range(rect.y, rect.y + rect.height), Range(rect.x, rect.x + rect.width));
    this->average_intensity = static_cast<int>(mean(roi).val[0]);
    return this->average_intensity;
    **/
     return 0;
}


void Armor::draw_Armor(Mat &image, cv::Point2f roi_offset, bool drawCenter) const {

//    Point2f vertices[4];
//    rect.points(vertices);
//    for (int i = 0; i < 4; i++)
//        line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//
//    std::vector<cv::Point> shape;
//    Point2f leftPoints[4];
//    this->left.rotatedRect.points(leftPoints);
//    Point2f rightPoints[4];
//    this->right.rotatedRect.points(rightPoints);
//    for (int i = 0; i < 4; i++) {
//        shape.push_back(leftPoints[i]);
//        shape.push_back(rightPoints[i]);
//    }
//    cv::RotatedRect ret = cv::minAreaRect(shape);

    Point2f vertices[4];
    this->rect.points(vertices);
    for (int i = 0; i < 4; i++)
        line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
}




    /**
    if(drawCenter) {
        circle(image, center + Point_<int>(roi_offset), int(rect.height / 4), Scalar(0, 0, 255), -1);
    }
     **/




bool Armor::Armor_constraints() {
    //TODO: read the Armor constraints from config file to tune the threshold.

    double distance = Euclidean_distance();
    double center_height_difference = this->center_height_difference();
    double height_ratio = this->height_ratio();
    double armor_width = width_two_center();
    double average_height = (left.rotatedRect.size.height + right.rotatedRect.size.height) / 2.f;
    double height_width_ratio = this->height_width_ratio();

    /**if (distance < 575.0f &&
        height_ratio < 1.5f &&
        left.rotatedRect.size.width < armor_width &&
        right.rotatedRect.size.width < armor_width &&
        3 * (left.rotatedRect.size.width + right.rotatedRect.size.wqidth) < armor_width && // to prevent two led bars closing to each other.
        center_height_difference < average_height &&//  to prevent excessive center difference in y-axis.
        height_width_ratio < 4.0 && height_ratio > 1) {
        std::cout << "true" << std::endl;
        return true;
    }**/
    //std::cout << "HEIGHT RATIO " << height_ratio << std::endl;
    //std::cout << "Angle Diff" << this->error_angle << std::endl;

    std::cout << "HWR " << height_width_ratio << std::endl;
    if (height_width_ratio < 0.2 && height_width_ratio > 0.1) {
        return true;
    }
//    if (this->error_angle < 45) return true;
//    return false;
    return false;
    if (height_ratio < 1.5f) return true;
    return false;


   // double height_ratio = this->height_ratio();
    //if (height_ratio < 1.5f) return true;
    //return false;
}

bool Armor::match_LEDs(const cv::Mat &img){
    //std::cout << get_average_intensity(img) << std::endl;
    //std::cout << get_average_intensity(img) << std::endl;
    //std::cout << Armor_constraints() << std::endl;
   //return Armor_constraints() && get_average_intensity(img) <= 10;
    return Armor_constraints() ;
}
