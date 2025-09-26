#pragma once
#include <memory>
#include <string_view>


namespace core {
struct ILogger {
virtual ~ILogger() = default;
virtual void log(std::string_view msg) = 0;
};


std::unique_ptr<ILogger> make_console_logger();
std::unique_ptr<ILogger> make_file_logger(std::string_view path);
} // namespace core