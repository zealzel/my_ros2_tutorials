#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"
#include <algorithm>
#include <chrono>
#include <memory>
#include <rclcpp/node.hpp>

using namespace std::chrono_literals;
using std_srvs::srv::Trigger;

class MySimpleNode : public rclcpp::Node,
                     public std::enable_shared_from ear dlass MySimpleNode : public rclcpp::Node {
  public:
    MySimpleNode() : Node("simple_node_multi") {
        cbg_me = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        cbg_re = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
        pub_ = this->create_publisher<std_msgs::msg::String>("my_word", 10);
        timer_ = this->create_wall_timer(500ms, [this]() {
            auto message = std_msgs::msg::String();
            message.data = "Hello, world!";
            pub_->publish(message);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        });
        RCLCPP_INFO(this->get_logger(), "I am here");
        srv_ = this->create_service<std_srvs::srv::Trigger>(
            "my_srv",
            [this](std_srvs::srv::Trigger::Request::SharedPtr req,
                   std_srvs::srv::Trigger::Response::SharedPtr res) {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                res->success = true;
                res->message = "Triggered!";
                RCLCPP_INFO(this->get_logger(), "srv called");
                return true;
            },
            rmw_qos_profile_services_default, cbg_re);
    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_;
    rclcpp::CallbackGroup::SharedPtr cbg_me;
    rclcpp::CallbackGroup::SharedPtr cbg_re;
};

int main(int argc, char** argv) {
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor exec;
    // MySimpleNode node = MySimpleNode(); // wrong
    rclcpp::Node::SharedPtr node = std::make_shared<MySimpleNode>();
    exec.add_node(node);
    exec.spin();

    rclcpp::shutdown();

    return 0;
}
