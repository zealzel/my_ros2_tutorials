#include "my_interfaces/msg/num.hpp"
#include "my_interfaces/msg/sphere.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class MyCustomPub : public rclcpp::Node {
  public:
    MyCustomPub() : Node("my_custom_pub") {
        pub_ = this->create_publisher<my_interfaces::msg::Num>("my_topic", 10);
        pub2_ = this->create_publisher<my_interfaces::msg::Sphere>("my_sphere_topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&MyCustomPub::timer_callback, this));
        timer2_ = this->create_wall_timer(100ms, std::bind(&MyCustomPub::timer2_callback, this));
        counter = 0;
    }

  private:
    void timer_callback() {
        auto message = my_interfaces::msg::Num();
        message.num = this->counter++;
        pub_->publish(message);
    }
    void timer2_callback() {
        auto message = my_interfaces::msg::Sphere();
        message.center.x = 0.3;
        message.center.y = 0.4;
        message.center.z = 0.2;
        message.radius = 1.2;
        pub2_->publish(message);
    }
    rclcpp::Publisher<my_interfaces::msg::Num>::SharedPtr pub_;
    rclcpp::Publisher<my_interfaces::msg::Sphere>::SharedPtr pub2_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timer2_;
    size_t counter;
};

int main(int argc, char* argv[]) {
    printf("my custom interfaces usage\n");
    // MyCustomPub my_custom_pub = std::make_shared<MyCustomPub>();
    rclcpp::init(argc, argv);
    // rclcpp::spin(my_custom_pub);
    rclcpp::spin(std::make_shared<MyCustomPub>());
    rclcpp::shutdown();
    return 0;
}
