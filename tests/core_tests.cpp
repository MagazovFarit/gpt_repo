#include <gtest/gtest.h>
#include <core/shapes.hpp>


TEST(Shapes, Areas) {
using namespace core;
std::vector<std::unique_ptr<IShape>> v;
v.emplace_back(std::make_unique<Circle>(2.0));
v.emplace_back(std::make_unique<Rect>(3.0, 4.0));
EXPECT_GT(total_area(v), 0.0);
}