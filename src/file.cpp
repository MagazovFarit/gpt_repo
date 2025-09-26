#include <core/file.hpp>
#include <string>


using namespace core;


File::File(std::string_view path, std::string_view mode) {
std::string p(path), m(mode);
f_ = std::fopen(p.c_str(), m.c_str());
if (!f_) throw std::runtime_error("fopen failed");
}


File::~File() {
if (f_) std::fclose(f_);
}


File::File(File&& other) noexcept : f_(std::exchange(other.f_, nullptr)) {}


File& File::operator=(File&& other) noexcept {
if (this != &other) {
if (f_) std::fclose(f_);
f_ = std::exchange(other.f_, nullptr);
}
return *this;
}


std::size_t File::write(const void* data, std::size_t size, std::size_t count) {
return std::fwrite(data, size, count, f_);
}


void File::flush() { if (f_) std::fflush(f_); }