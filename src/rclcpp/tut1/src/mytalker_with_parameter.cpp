#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <memory>

using namespace std::chrono_literals;

class MyTalker : public rclcpp::Node {
  public:
    MyTalker() : Node("my_talker") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&MyTalker::timer_callback, this));
        this->declare_parameter<std::string>("sentence", "Hello!!, world!");
    }

  private:
    void timer_callback() {
        std::string my_message =
            this->get_parameter("sentence").get_parameter_value().get<std::string>();

        auto message = std_msgs::msg::String();

        // message.data = "Hello, world! " + std::to_string(count_++);
        message.data = my_message;

        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyTalker>());
    rclcpp::shutdown();
    return 0;
}
