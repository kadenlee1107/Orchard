#pragma once

#include <cstdarg>
#include <cstdio>
#include <string>

namespace orchard {

inline std::string formatMessage(const char* fmt, va_list args) {
    va_list copy;
    va_copy(copy, args);
    const int length = std::vsnprintf(nullptr, 0, fmt, copy);
    va_end(copy);
    std::string buffer(length + 1, '\0');
    std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
    buffer.pop_back();
    return buffer;
}

inline void logImpl(const char* level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string message = formatMessage(fmt, args);
    va_end(args);
    std::fprintf(stderr, "[Orchard][%s] %s\n", level, message.c_str());
}

#define ORCHARD_LOG_INFO(fmt, ...) \
    orchard::logImpl("INFO", fmt, ##__VA_ARGS__)

#define ORCHARD_LOG_WARN(fmt, ...) \
    orchard::logImpl("WARN", fmt, ##__VA_ARGS__)

#define ORCHARD_LOG_ERROR(fmt, ...) \
    orchard::logImpl("ERROR", fmt, ##__VA_ARGS__)

}
