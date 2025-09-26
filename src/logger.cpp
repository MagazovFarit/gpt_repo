#include <core/logger.hpp>
#include <core/file.hpp>
#include <cstdio>
#include <string>


using namespace core;


namespace {
struct ConsoleLogger : ILogger {
void log(std::string_view msg) override {
std::fwrite(msg.data(), 1, msg.size(), stdout); std::fputc('\n', stdout); std::fflush(stdout);
}
};


struct FileLogger : ILogger {
File f;
explicit FileLogger(std::string_view p) : f(p, "a") {}
void log(std::string_view msg) override {
f.write(msg.data(), 1, msg.size()); f.write("\n", 1, 1); f.flush();
}
};
} // namespace


std::unique_ptr<ILogger> core::make_console_logger() { return std::make_unique<ConsoleLogger>(); }
std::unique_ptr<ILogger> core::make_file_logger(std::string_view path) { return std::make_unique<FileLogger>(path); }