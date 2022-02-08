#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t &coordinate, double radius):
  point_(coordinate),
  radius_(radius)
{
  if(radius_ <= 0)
  {
    throw std::invalid_argument("Incorrect value of the radius.");
  }
}

double Circle::getArea() const
{
  return M_PI * std::pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, point_};
}

void Circle::move(const point_t &coordinate)
{
  point_ = coordinate;
}

void Circle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void Circle::print(std::ostream& out) const
{
  out << "Circle" << '\n' << "{ point_.x = " << point_.x << ", point.y = "
      << point_.y << ", radius_ = " << radius_ << "} \n";
}
