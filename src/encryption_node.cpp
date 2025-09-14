#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "encryption_system/crypto_utils.h"

class EncryptionNode : public rclcpp::Node {
public:
    EncryptionNode() : Node("encryption_node") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/original_message", 10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
	    	std::string encrypted_data = 
			encryption_system::CryptoUtils::xor_encrypt(msg->data, encryption_system::CryptoUtils::SECRET_KEY);

		std::string hex_encrypted = 
			encryption_system::CryptoUtils::bytes_to_hex(encrypted_data);
			
                auto encrypted_msg = std_msgs::msg::String();
                encrypted_msg.data = hex_encrypted;
		publisher_->publish(encrypted_msg);
                RCLCPP_INFO(this->get_logger(), "Encrypting...");
	       	RCLCPP_INFO(this->get_logger(), "Encrypted: '%s'", hex_encrypted.c_str());
   	});
        
        publisher_ = this->create_publisher<std_msgs::msg::String>("/encrypted_message", 10);
        RCLCPP_INFO(this->get_logger(), "Encryption node started, encrypting with KEY");
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EncryptionNode>());
    rclcpp::shutdown();
    return 0;
}
