#include <core/shapes.hpp>
#include <cmath>
#include <numeric>


using namespace core;


double Circle::area() const { return M_PI * r * r; }


double Rect::area() const { return w * h; }


double core::total_area(const std::vector<std::unique_ptr<IShape>>& v) {
double sum = 0.0;
for (auto& s : v) sum += s->area();
return sum;
}