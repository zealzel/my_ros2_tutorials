#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

using namespace std::chrono_literals;

class MyListener : public rclcpp::Node {
  public:
    MyListener() : Node("my_listener") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "chatter", 10, std::bind(&MyListener::topic_callback, this, _1));
    }

  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyListener>());
    rclcpp::shutdown();
    return 0;
}
