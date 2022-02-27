// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "opencv2/core/types.hpp"
//#include "opencv2/highgui.hpp"
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
//#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

long send_data(){
    cv::Point2f pitchYaw(180.0,90.0);
    long data = int(pitchYaw.x) | int(pitchYaw.y) << 32;
    //std::cout << data << std::endl;
    //data |= int(pitchYaw.y);

    return data;
}



class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
      //publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      publisher_ = this->create_publisher<std_msgs::msg::Int32>("/gimbal_data", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }


private:
  void timer_callback()
  {
    //auto message = std_msgs::msg::String();
    //message.data = send_data() + std::to_string(count_++);
    //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    //publisher_->publish(message);
    auto message = std_msgs::msg::Int32();
    //std::cout << typeid(message.data).name() << std::endl;
    message.data = send_data();

    std::string pitch = std::to_string(message.data >> 32);
    std::string yaw = std::to_string(message.data);
    RCLCPP_INFO(this->get_logger(), "Publishing: 'pitch: %s'", pitch.c_str());
    RCLCPP_INFO(this->get_logger(), "Publishing: 'yaw: %s'", yaw.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  //rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
