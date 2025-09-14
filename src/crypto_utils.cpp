#include "encryption_system/crypto_utils.h"
#include <sstream>
#include <iomanip>

namespace encryption_system {

const std::string CryptoUtils::SECRET_KEY = "YouJUstDOntGuessTHIS123";

std::string CryptoUtils::xor_encrypt(const std::string& input, const std::string& key) {
    std::string output = input;
    
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key.size()];
    }
    
    return output;
}

std::string CryptoUtils::xor_decrypt(const std::string& input, const std::string& key) {
    // XOR 加密和解密使用相同的函數
    return xor_encrypt(input, key);
}

std::string CryptoUtils::bytes_to_hex(const std::string& input) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (unsigned char c : input) {
        ss << std::setw(2) << static_cast<int>(c);
    }
    
    return ss.str();
}

std::string CryptoUtils::hex_to_bytes(const std::string& hex) {
    std::string bytes;
    
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = static_cast<char>(strtol(byteString.c_str(), nullptr, 16));
        bytes.push_back(byte);
    }
    
    return bytes;
}

} // namespace encryption_system
