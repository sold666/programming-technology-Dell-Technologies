#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t &coordinate, double width, double height):
  point_(coordinate),
  width_(width),
  height_(height)
{
  if ((width_ <= 0) || (height_ <= 0))
  {
    throw std::invalid_argument("Incorrect width and height value.");
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {height_ , width_, point_};
}

void Rectangle::move(const point_t &coordinate)
{
  point_ = coordinate;
}

void Rectangle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void Rectangle::print(std::ostream& out) const
{
  out << "Rectangle" << '\n' << "{ point_.x = " << point_.x << ", point.y = "
      << point_.y << ", width = " << width_ << ", height = " << height_ << "}\n";
}
