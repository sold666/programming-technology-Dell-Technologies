#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

korzh::Circle::Circle(const point_t &coordinate, double radius):
  point_(coordinate),
  radius_(radius)
{
  if(radius_ <= 0)
  {
    throw std::invalid_argument("Incorrect value of the radius.");
  }
}

double korzh::Circle::getArea() const
{
  return M_PI * std::pow(radius_, 2);
}

korzh::rectangle_t korzh::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, point_};
}

void korzh::Circle::move(const point_t &coordinate)
{
  point_ = coordinate;
}

void korzh::Circle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void korzh::Circle::print(std::ostream& out) const
{
  out << "Circle" << '\n' << "{ point_.x = " << point_.x << ", point.y = "
      << point_.y << ", radius_ = " << radius_ << "} \n";
}

void korzh::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient.");
  }
  radius_ *= coefficient;
}

double korzh::Circle::getRadius() const
{
  return radius_;
}
