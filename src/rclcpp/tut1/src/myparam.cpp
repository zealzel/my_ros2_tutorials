#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <algorithm>
#include <chrono>
#include <memory>

using std::placeholders::_1;

using namespace std::chrono_literals;

class myParam : public rclcpp::Node {
  public:
    myParam(const std::string& name) : Node(name) {
        this->declare_parameter("name", "default_name");
        this->declare_parameter("x_pos", 0);
        this->declare_parameter("y_pos", 0);
        this->declare_parameter("z_pos", 0);
        this->declare_parameter("is_ok", true);
        sub_ = this->create_subscription<std_msgs::msg::String>(
            "changeName", 10, std::bind(&myParam::myTopicCallback, this, _1));
        pub_ = this->create_publisher<std_msgs::msg::String>("my_info", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&myParam::myTimerCallback, this));
        RCLCPP_INFO(this->get_logger(), "started");
    }

  private:
    std::string myTopic;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    void myTimerCallback() {
        std_msgs::msg::String msg = std_msgs::msg::String();
        std::string name = this->get_parameter("name").as_string();
        int x_pos = this->get_parameter("x_pos").as_int();
        int y_pos = this->get_parameter("y_pos").as_int();
        bool is_ok = this->get_parameter("is_ok").as_bool();
        std::string isOK = is_ok ? "true" : "false";
        msg.data = "name: " + name + "|x_pos: " + std::to_string(x_pos) +
                   "|y_pos: " + std::to_string(y_pos) + "|is_ok: " + isOK;
        RCLCPP_INFO(this->get_logger(), "myTimerCallback: [%s]", msg.data.c_str());
        pub_->publish(msg);
    }

    void myTopicCallback(std_msgs::msg::String::SharedPtr msg) {
        //
        std::vector<rclcpp::Parameter> all_new_parameters{
            rclcpp::Parameter("name", msg->data), rclcpp::Parameter("x_pos", 10),
            rclcpp::Parameter("y_pos", 20), rclcpp::Parameter("is_ok", true)};
        this->set_parameters(all_new_parameters);

        RCLCPP_INFO(this->get_logger(), "chnageName: [%s]", msg->data.c_str());
    }

    // void on_parameter_event(const rclcpp::ParameterEvent& event) {
    //     if (event.get_name() == "name") {
    //         RCLCPP_INFO(this->get_logger(), "name changed to %s",
    //         event.get_new_value().c_str());
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

    // create a Node pointer named "myparam_node"
    auto myparam_node = std::make_shared<myParam>("myparam_node");

    rclcpp::spin(myparam_node);

    rclcpp::shutdown();
    return 0;
}
