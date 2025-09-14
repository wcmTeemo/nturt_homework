#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class DecryptionNode : public rclcpp::Node {
public:
    DecryptionNode() : Node("decryption_node") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/encrypted_message", 10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
                auto decrypted_msg = std_msgs::msg::String();
                // 簡單的"解密" - 移除"ENCRYPTED: "前綴
                if (msg->data.find("ENCRYPTED: ") == 0) {
                    decrypted_msg.data = msg->data.substr(11);
                } else {
                    decrypted_msg.data = msg->data;
                }
                publisher_->publish(decrypted_msg);
                RCLCPP_INFO(this->get_logger(), "Decrypted: '%s'", decrypted_msg.data.c_str());
            });
        
        publisher_ = this->create_publisher<std_msgs::msg::String>("/decrypted_message", 10);
        RCLCPP_INFO(this->get_logger(), "Decryption node started");
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DecryptionNode>());
    rclcpp::shutdown();
    return 0;
}
