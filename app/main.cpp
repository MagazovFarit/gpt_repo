#include <core/logger.hpp>
#include <memory>


int main() {
auto log = core::make_console_logger();
log->log("Hello, C++ World!");
}