#include "rectangle.hpp"
#include <stdexcept>

korzh::Rectangle::Rectangle(const point_t &coordinate, double width, double height):
  point_(coordinate),
  width_(width),
  height_(height)
{
  if ((width_ <= 0) || (height_ <= 0))
  {
    throw std::invalid_argument("Incorrect width and height value.");
  }
}

double korzh::Rectangle::getArea() const
{
  return height_ * width_;
}

korzh::rectangle_t korzh::Rectangle::getFrameRect() const
{
  return {width_, height_, point_};
}

void korzh::Rectangle::move(const point_t &coordinate)
{
  point_ = coordinate;
}

void korzh::Rectangle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void korzh::Rectangle::print(std::ostream& out) const
{
  out << "Rectangle" << '\n' << "{ point_.x = " << point_.x << ", point.y = "
      << point_.y << ", width = " << width_ << ", height = " << height_ << "}\n";
}

void korzh::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Incorrect coefficient.");
  }
  height_ *= coefficient;
  width_ *= coefficient;
}
