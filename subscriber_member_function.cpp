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

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/int8.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    //subscription_ = this->create_subscription<std_msgs::msg::String>(
      //"topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
     subscription_ = this->create_subscription<std_msgs::msg::Int8>(
             "/referee/team_color", 10, "/referee/robot_type", 10,std::bind(&MinimalSubscriber::topic_callback, this, _1));
     subscription_ =
  }

private:
  void topic_callback(const std_msgs::msg::Int8::SharedPtr msg) const
  {

    //std::string pitch= std::to_string(msg->data[0]);
    //std::string yaw = std::to_string(msg->data[1]);
    //RCLCPP_INFO(this->get_logger(), "I heard: 'pitch: %s'", pitch.c_str());
    //RCLCPP_INFO(this->get_logger(), "I heard: 'yaw: %s'", yaw.c_str());
  }
  //rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::Subscription<std_msgs::msg::Int8>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
