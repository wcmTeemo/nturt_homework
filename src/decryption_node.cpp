#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "encryption_system/crypto_utils.h"

using namespace std::chrono_literals;

class DecryptionNode : public rclcpp::Node {
public:
    DecryptionNode() : Node("decryption_node") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/encrypted_message", 10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
                try {
			std::string binary_data = 
				encryption_system::CryptoUtils::hex_to_bytes(msg->data);
				
			std::string decrypted_data = 
				encryption_system::CryptoUtils::xor_decrypt(binary_data, encryption_system::CryptoUtils::SECRET_KEY);
				
		auto decrypted_msg = std_msgs::msg::String();
         	decrypted_msg.data = decrypted_data;      	
                publisher_->publish(decrypted_msg);
		
		RCLCPP_INFO(this->get_logger(), "Decrypting...");
                RCLCPP_INFO(this->get_logger(), "encrypted: '%s'", msg->data.c_str());
                RCLCPP_INFO(this->get_logger(), "decrypted: '%s'", decrypted_data.c_str());
                RCLCPP_INFO(this->get_logger(), "============");

	     } catch (const std::exception& e) {
		RCLCPP_ERROR(this->get_logger(), "Decrypt FAILURE: %s", e.what());
             }
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
