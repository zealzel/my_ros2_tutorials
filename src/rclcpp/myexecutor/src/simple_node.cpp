#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char** argv) {
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);

    // create a Node pointer named "some_node"
    auto some_node = std::make_shared<rclcpp::Node>("some_node");

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_ =
        some_node->create_publisher<std_msgs::msg::String>("my_word", 10);

    rclcpp::TimerBase::SharedPtr timer_ = some_node->create_wall_timer(500ms, [pub_, some_node]() {
        auto message = std_msgs::msg::String();
        message.data = "Hello, world!";
        pub_->publish(message);
        RCLCPP_INFO(some_node->get_logger(), "Publishing: '%s'", message.data.c_str());
    });

    rclcpp::Logger logger = some_node->get_logger();
    RCLCPP_INFO(logger, "I am here");

    // rclcpp::spin(std::make_shared<rclcpp::Node>("some_node"));
    rclcpp::spin(some_node);

    rclcpp::shutdown();
    return 0;
}
