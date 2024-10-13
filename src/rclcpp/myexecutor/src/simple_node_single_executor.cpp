#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <algorithm>
#include <chrono>
#include <memory>
#include <rclcpp/node.hpp>

using namespace std::chrono_literals;

class MySimpleNode : public rclcpp::Node {
  public:
    MySimpleNode() : Node("my_node") {
        pub_ = this->create_publisher<std_msgs::msg::String>("my_word", 10);
        timer_ = this->create_wall_timer(500ms, [this]() {
            auto message = std_msgs::msg::String();
            message.data = "Hello, world!";
            pub_->publish(message);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        });
        RCLCPP_INFO(this->get_logger(), "I am here");
    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
};

int main(int argc, char** argv) {
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);
    rclcpp::executors::SingleThreadedExecutor exec;
    // MySimpleNode node = MySimpleNode(); // wrong
    rclcpp::Node::SharedPtr node = std::make_shared<MySimpleNode>();
    exec.add_node(node);
    exec.spin();

    rclcpp::shutdown();

    return 0;
}
