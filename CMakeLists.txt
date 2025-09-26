cmake_minimum_required(VERSION 3.20)
project(TextPipeline LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


option(ENABLE_SANITIZERS "Enable ASan/UBSan in Debug" ON)
if (ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE MATCHES "Debug")
add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
add_link_options(-fsanitize=address,undefined)
endif()


add_library(core
src/file.cpp
src/logger.cpp
src/shapes.cpp
)


target_include_directories(core PUBLIC include)


if (MSVC)
target_compile_options(core PRIVATE /W4)
else()
target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic)
endif()


add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE core)


# --- Tests ---
include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(core_tests tests/core_tests.cpp)


if (MSVC)
target_compile_options(core_tests PRIVATE /W4)
else()
target_compile_options(core_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()


target_link_libraries(core_tests PRIVATE core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(core_tests)
