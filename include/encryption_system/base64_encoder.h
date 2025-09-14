#ifndef ENCRYPTION_SYSTEM_BASE64_ENCODER_H
#define ENCRYPTION_SYSTEM_BASE64_ENCODER_H

#include <string>

namespace encryption_system {

class Base64Encoder {
public:
    static std::string encode(const std::string& input);
    static std::string decode(const std::string& input);
};

} // namespace encryption_system

#endif
