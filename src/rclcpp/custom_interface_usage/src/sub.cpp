#include "my_interfaces/msg/num.hpp"
#include "my_interfaces/msg/sphere.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

using namespace std::chrono_literals;

class MyCustomSub : public rclcpp::Node {
  public:
    MyCustomSub() : Node("my_custom_sub") {
        sub1_ = this->create_subscription<my_interfaces::msg::Num>(
            "my_sphere_topic", 10, std::bind(&MyCustomSub::topic1_callback, this, _1));
        sub2_ = this->create_subscription<my_interfaces::msg::Sphere>(
            "my_sphere_topic", 10, std::bind(&MyCustomSub::topic2_callback, this, _1));
    }

  private:
    void topic1_callback(const my_interfaces::msg::Num::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "num: %ld", msg->num);
    }
    void topic2_callback(const my_interfaces::msg::Sphere::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "center.x: %f", msg->center.x);
    }
    rclcpp::Subscription<my_interfaces::msg::Num>::SharedPtr sub1_;
    rclcpp::Subscription<my_interfaces::msg::Sphere>::SharedPtr sub2_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyCustomSub>());
    rclcpp::shutdown();
    return 0;
}
