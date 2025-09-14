#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node {
public:
    PublisherNode() : Node("publisher_node") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("/original_message", 10);
        timer_ = this->create_wall_timer(
            1000ms,
            std::bind(&PublisherNode::timer_callback, this));
        
        RCLCPP_INFO(this->get_logger(), "Publisher node started");
    }

private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "Hello World! Count: " + std::to_string(count_++);
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "Published: '%s'", message.data.c_str());
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    int count_ = 0;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}
