#ifndef ENCRYPTION_SYSTEM_CRYPTO_UTILS_H
#define ENCRYPTION_SYSTEM_CRYPTO_UTILS_H

#include <string>
#include <vector>

namespace encryption_system {

class CryptoUtils {
public:
    static std::string xor_encrypt(const std::string& input, const std::string& key);
    static std::string xor_decrypt(const std::string& input, const std::string& key);
    static std::string bytes_to_hex(const std::string& input);
    static std::string hex_to_bytes(const std::string& hex);

    static const std::string SECRET_KEY;
};
} // namespace encryption_system

#endif // ENCRYPTION_SYSTEM_CRYPTO_UTILS_H
