#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &coordinate, double width, double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &coordinate) override;
  void move(double dx, double dy) override;
  void print(std::ostream& out) const override;

private:
  point_t point_;
  double width_;
  double height_;
};

#endif
