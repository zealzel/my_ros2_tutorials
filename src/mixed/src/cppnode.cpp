#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class CppNode : public rclcpp::Node {
  public:
    CppNode() : Node("cppnode") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&CppNode::timer_callback, this));
    }

  private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "I am Keivn Lee";
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
    // CppNode* node = std::make_shared<CppNode>();
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CppNode>());

    return 0;
}
