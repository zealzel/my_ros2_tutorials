#include "std_msgs/msg/string.hpp"
#include <memory>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MyTalkerComp : public rclcpp::Node {
  public:
    MyTalkerComp(const rclcpp::NodeOptions& options) : Node("my_talker", options) {
        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ = this->create_wall_timer(50ms, std::bind(&MyTalkerComp::timer_callback, this));
    }

  private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(MyTalkerComp)
