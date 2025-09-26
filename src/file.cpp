#include <core/file.hpp>
#include <string>


using namespace core;


File::File(std::string_view path, std::string_view mode) {
std::string p(path), m(mode);
f_ = std::fopen(p.c_str(), m.c_str());
if (!f_) throw std::runtime_error("fopen failed");
}


File::~File() {
    if (f_ && !keepOpen)
        std::fclose(f_);
}

File::File(FILE* f)
{
    f_ = f;
    keepOpen = true;
}

File::File(File&& other) noexcept : f_(std::exchange(other.f_, nullptr)) {}


File& File::operator=(File&& other) noexcept {
if (this != &other) {
if (f_) std::fclose(f_);
f_ = std::exchange(other.f_, nullptr);
}
return *this;
}

size_t File::read(void* data, size_t size, size_t count)
{
    return std::fread(data, size, count, f_);
}

std::size_t File::write(const void* data, std::size_t size, std::size_t count)
{
    return std::fwrite(data, size, count, f_);
}

void File::flush() { if (f_) std::fflush(f_); }

int File::fseek(FILE* stream, long offset, int origin)
{
    return std::fseek(stream, offset, origin);
}

long File::ftell(FILE* stream)
{
    return std::ftell(stream);
}
