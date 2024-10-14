#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"
#include <algorithm>
#include <chrono>
#include <memory>
#include <rclcpp/node.hpp>

using namespace std::chrono_literals;
using std_srvs::srv::Trigger;

class MySimpleNode : public rclcpp::Node {
  public:
    MySimpleNode() : Node("simple_node_single") {
        pub_ = this->create_publisher<std_msgs::msg::String>("my_word", 10);
        timer_ = this->create_wall_timer(500ms, [this]() {
            auto message = std_msgs::msg::String();
            message.data = "Hello, world!";
            pub_->publish(message);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        });
        RCLCPP_INFO(this->get_logger(), "I am here");
        srv_ = this->create_service<std_srvs::srv::Trigger>(
            "my_srv", [this](std_srvs::srv::Trigger::Request::SharedPtr req,
                             std_srvs::srv::Trigger::Response::SharedPtr res) {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                res->success = true;
                res->message = "Triggered!";
                RCLCPP_INFO(this->get_logger(), "srv called");
                return true;
            });
    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_;
};

int main(int argc, char** argv) {
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MySimpleNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
