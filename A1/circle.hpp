#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &coordinate, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &coordinate) override;
  void move(double dx, double dy) override;
  void print(std::ostream& out) const override;

private:
  point_t point_;
  double radius_;
};

#endif
