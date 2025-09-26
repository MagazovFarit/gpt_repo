#pragma once
#include <cstdio>
#include <string_view>
#include <utility>
#include <stdexcept>


namespace core {
class File {
std::FILE* f_ = nullptr;
public:
File() = default;
File(std::string_view path, std::string_view mode);
~File();


File(const File&) = delete;
File& operator=(const File&) = delete;


File(File&& other) noexcept;
File& operator=(File&& other) noexcept;


explicit operator bool() const noexcept { return f_ != nullptr; }
std::FILE* get() const noexcept { return f_; }


std::size_t write(const void* data, std::size_t size, std::size_t count);
void flush();
};
} // namespace core