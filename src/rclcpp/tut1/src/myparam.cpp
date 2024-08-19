#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <algorithm>
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class myParam : public rclcpp::Node {
  public:
    myParam(const std::string& name) : Node(name) {
        this->declare_parameter("name", "karthik");
        this->declare_parameter("x_pos", 10);
        this->declare_parameter("y_pos", 20);
        this->declare_parameter("is_ok", true);
    }

    // void on_parameter_event(const rclcpp::ParameterEvent& event) {
    //     if (event.get_name() == "name") {
    //         RCLCPP_INFO(this->get_logger(), "name changed to %s", event.get_new_value().c_str());
    //     } else if (event.get_name() == "x_pos") {
    //         RCLCPP_INFO(this->get_logger(), "x_pos changed to %d",
    //         event.get_new_value().as_int());
    //     } else if (event.get_name() == "y_pos") {
    //         RCLCPP_INFO(this->get_logger(), "y_pos changed to %d",
    //         event.get_new_value().as_int());
    //     } else if (event.get_name() == "is_ok") {
    //         RCLCPP_INFO(this->get_logger(), "is_ok changed to %s",
    //         event.get_new_value().c_str());
    //     }
    // }
};

int main(int argc, char** argv) {
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);

    // create a Node pointer named "some_node"
    auto some_node = std::make_shared<myParam>("some_node");

    rclcpp::spin(some_node);

    rclcpp::shutdown();
    return 0;
}
