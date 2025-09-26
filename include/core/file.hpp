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

File(FILE* f);

File(const File&) = delete;
File& operator=(const File&) = delete;


File(File&& other) noexcept;
File& operator=(File&& other) noexcept;


explicit operator bool() const noexcept { return f_ != nullptr; }
std::FILE* get() const noexcept { return f_; }

std::size_t read(void* data, std::size_t size, std::size_t count);

std::size_t write(const void* data, std::size_t size, std::size_t count);
void flush();

int fseek(std::FILE* stream, long offset, int origin) noexcept;

long ftell(std::FILE* stream) noexcept;

private:
bool keepOpen{false};
};
} // namespace core
