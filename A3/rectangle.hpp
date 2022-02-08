#ifndef A3_RECTANGLE_HPP
#define A3_RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace korzh
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &coordinate, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &coordinate) override;
    void move(double dx, double dy) override;
    void print(std::ostream& out) const override;
    void scale(double coefficient) override;

  private:
    point_t point_;
    double width_;
    double height_;
  };
}

#endif
