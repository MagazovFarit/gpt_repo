#pragma once
#include <memory>
#include <vector>


namespace core {
struct IShape {
virtual ~IShape() = default;
virtual double area() const = 0;
};


struct Circle final : IShape {
double r{};
explicit Circle(double rr) : r(rr) {}
double area() const override;
};


struct Rect final : IShape {
double w{}, h{};
Rect(double ww, double hh) : w(ww), h(hh) {}
double area() const override;
};


double total_area(const std::vector<std::unique_ptr<IShape>>& v);
} // namespace core