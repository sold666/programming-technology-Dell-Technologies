#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <iostream>
#include <memory>

#include "shape.hpp"

namespace korzh
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &figure);
    CompositeShape(CompositeShape &&figure) noexcept;
    ~CompositeShape() override = default;
    CompositeShape& operator=(const CompositeShape &rValue);
    CompositeShape& operator=(CompositeShape &&rValue) noexcept ;
    std::shared_ptr<Shape> operator[](size_t index);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &coordinate) override;
    void move(double dx, double dy) override;
    void print(std::ostream &out) const override;
    size_t getSize() const;
    void scale(double coefficient) override;
    void add(const std::shared_ptr<Shape> &shape);
    void remove(size_t index);

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
  };
}

#endif
