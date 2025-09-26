#include <core/file.hpp>
#include <core/logger.hpp>
#include <cstdio>
#include <string>
#include <vector>

using namespace core;

namespace {
struct ConsoleLogger : ILogger {
void log(std::string_view msg) override {
std::fwrite(msg.data(), 1, msg.size(), stdout); std::fputc('\n', stdout); std::fflush(stdout);
}
};


struct FileLogger : ILogger {
    enum class lvl { info = 0, warn, error, count };
    std::vector<std::string_view> lvl_msg{"info: ", "warn: ", "error: "};
    File f;
    std::string_view mode;
    explicit FileLogger(std::string_view p, std::string_view m = "a")
        : f(p, m)
    {}
    void log(std::string_view msg) override
    {
        f.write(msg.data(), 1, msg.size());
        f.write("\n", 1, 1);
        f.flush();
    }
    void log(std::string_view msg, lvl l)
    {
        f.write(&lvl_msg[(unsigned long long) l], 1, lvl_msg[(unsigned long long) l].size());
        log(msg);
    }
};
} // namespace


std::unique_ptr<ILogger> core::make_console_logger() { return std::make_unique<ConsoleLogger>(); }
std::unique_ptr<ILogger> core::make_file_logger(std::string_view path) { return std::make_unique<FileLogger>(path); }
