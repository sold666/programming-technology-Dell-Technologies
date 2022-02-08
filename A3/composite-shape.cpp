#include "composite-shape.hpp"
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <ostream>
#include "base-types.hpp"

korzh::CompositeShape::CompositeShape() :
  size_(0)
{}

korzh::CompositeShape::CompositeShape(const CompositeShape &figure) :
  size_(figure.size_)
{
  if (figure.size_ > 0)
  {
    shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(figure.size_);
    size_ = figure.size_;
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i] = figure.shapes_[i];
    }
  }
}

korzh::CompositeShape::CompositeShape(CompositeShape &&figure) noexcept:
  shapes_(std::move(figure.shapes_)),
  size_(figure.size_)
{
  figure.size_ = 0;
}

korzh::CompositeShape &korzh::CompositeShape::operator=(const korzh::CompositeShape &rValue)
{
  if (this == &rValue)
  {
    return *this;
  }
  if (rValue.size_ != 0)
  {
    shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(rValue.size_);
    size_ = rValue.size_;
    for (size_t i = 0; i < size_; ++i)
    {
      shapes_[i] = rValue.shapes_[i];
    }
  }
  else
  {
    shapes_ = nullptr;
    size_ = 0;
  }
  return *this;
}

korzh::CompositeShape &korzh::CompositeShape::operator=(korzh::CompositeShape &&rValue) noexcept
{
  if (this == &rValue)
  {
    return *this;
  }
  if (rValue.size_ != 0)
  {
    size_ = rValue.size_;
    shapes_ = std::move(rValue.shapes_);
    rValue.size_ = 0;
  }
  else
  {
    shapes_ = nullptr;
    size_ = 0;
  }
  return *this;
}

std::shared_ptr<korzh::Shape> korzh::CompositeShape::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("The index went out of bounds.");
  }
  return shapes_[index];
}

double korzh::CompositeShape::getArea() const
{
  double totalArea = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    totalArea += shapes_[i]->getArea();
  }
  return totalArea;
}

korzh::rectangle_t korzh::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return {0, 0, {0, 0}};
  }
  rectangle_t currentRectangle = {0, 0, {0, 0}};
  size_t i = 0;
  for (; i < size_; ++i)
  {
    currentRectangle = shapes_[i]->getFrameRect();
    if (currentRectangle.width != 0)
    {
      break;
    }
  }
  if (currentRectangle.width == 0)
  {
    return {0, 0, {0, 0}};
  }
  double maxX = currentRectangle.pos.x + currentRectangle.width / 2;
  double maxY = currentRectangle.pos.y + currentRectangle.height / 2;

  double minX = currentRectangle.pos.x - currentRectangle.width / 2;
  double minY = currentRectangle.pos.y - currentRectangle.height / 2;

  for (; i < size_; ++i)
  {
    if (shapes_[i]->getFrameRect().width == 0)
    {
      continue;
    }
    maxX = std::max(shapes_[i]->getFrameRect().pos.x + shapes_[i]->getFrameRect().width / 2, maxX);
    maxY = std::max(shapes_[i]->getFrameRect().pos.y + shapes_[i]->getFrameRect().height / 2, maxY);

    minX = std::min(shapes_[i]->getFrameRect().pos.x - shapes_[i]->getFrameRect().width / 2, minX);
    minY = std::min(shapes_[i]->getFrameRect().pos.y - shapes_[i]->getFrameRect().height / 2, minY);
  }

  return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
}

void korzh::CompositeShape::move(const korzh::point_t &coordinate)
{
  const rectangle_t frameRect = getFrameRect();
  move(coordinate.x - frameRect.pos.x, coordinate.y - frameRect.pos.y);
}

void korzh::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapes_[i]->move(dx, dy);
  }
}

void korzh::CompositeShape::print(std::ostream &out) const
{
  for (size_t i = 0; i < size_; ++i)
  {
    shapes_[i]->print(out);
  }
}

size_t korzh::CompositeShape::getSize() const
{
  return size_;
}

void korzh::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient was non-positive");
  }
  const rectangle_t frameRect = getFrameRect();
  for (size_t i = 0; i < size_; ++i)
  {
    const rectangle_t frameRectPos = shapes_[i]->getFrameRect();
    shapes_[i]->scale(coefficient);
    const double dx = frameRect.pos.x + coefficient * (frameRectPos.pos.x  - frameRect.pos.x);
    const double dy = frameRect.pos.y + coefficient * (frameRectPos.pos.y- frameRect.pos.y);
    shapes_[i]->move({dx, dy});
  }
}

void korzh::CompositeShape::add(const std::shared_ptr<Shape> &figure)
{
  if (this == figure.get())
  {
    throw std::logic_error("You can't add the same CompositeShape.");
  }
  if (figure == nullptr)
  {
    throw std::invalid_argument("You can't add empty shape.");
  }
  for (size_t i = 0; i < size_; ++i)
  {
    if (figure == shapes_[i])
    {
      throw std::logic_error("The shape has already been added");
    }
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> temp = std::make_unique<std::shared_ptr<Shape>[]>(size_ + 1);
  for (size_t i = 0; i < size_; ++i)
  {
    temp[i] = shapes_[i];
  }
  shapes_ = std::move(temp);
  shapes_[size_] = figure;
  ++size_;
}

void korzh::CompositeShape::remove(size_t index)
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty.");
  }
  if (index >= size_)
  {
    throw std::out_of_range("The index went out of bounds.");
  }
  for (size_t i = index; i < size_ - 1; ++i)
  {
    shapes_[i] = std::move(shapes_[i + 1]);
  }
  --size_;
}
