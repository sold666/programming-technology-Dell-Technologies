#ifndef A3_SHAPE_HPP
#define A3_SHAPE_HPP

#include <iostream>

namespace korzh
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &coordinate) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void scale(double coefficient) = 0;
  };
}

#endif
