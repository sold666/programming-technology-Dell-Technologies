#include <iostream>
#include <stdexcept>
#include <memory>
#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

void demonstrateFunctionShape(korzh::Shape* shape);
void demonstrateFunctionCompositeShape(korzh::CompositeShape& compositeShape);

int main()
{
  const korzh::point_t COORDINATE_ONE = {33.2, -332.111};
  const double WIDTH = 2.5;
  const double HEIGHT = 2.5;
  try
  {
    korzh::Rectangle figureOne(COORDINATE_ONE, WIDTH, HEIGHT);
    korzh::Shape *figureOne_ptr = &figureOne;
    demonstrateFunctionShape(figureOne_ptr);
  }
  catch (const std::invalid_argument &error)
  {
    std::cout << error.what();
    return 1;
  }

  const korzh::point_t COORDINATE_TWO = {44.2,55.1};
  const double RADIUS = 3.0;
  try
  {
    korzh::Circle figureTwo(COORDINATE_TWO, RADIUS);
    korzh::Shape *figureTwo_ptr = &figureTwo;
    demonstrateFunctionShape(figureTwo_ptr);
  }
  catch (const std::invalid_argument &error)
  {
    std::cout << error.what();
    return 1;
  }

  std::shared_ptr<korzh::Shape> circle;
  std::shared_ptr<korzh::Shape> rectangle;
  korzh::CompositeShape compositeShape;
  try
  {
    circle = std::make_shared<korzh::Circle>(COORDINATE_TWO, RADIUS);
    rectangle = std::make_shared<korzh::Rectangle>(COORDINATE_ONE, WIDTH, HEIGHT);
  }
  catch (const std::invalid_argument &error)
  {
    std::cout << error.what();
    return 1;
  }
  catch (const std::bad_alloc &error)
  {
    std::cout << error.what();
    return 1;
  }
  try
  {
    compositeShape.add(circle);
    compositeShape.add(rectangle);
    demonstrateFunctionCompositeShape(compositeShape);
  }
  catch (const std::invalid_argument &error)
  {
    std::cout << error.what();
    return 1;
  }
  catch (const std::logic_error &error)
  {
    std::cout << error.what();
    return 1;
  }
  try
  {
    compositeShape.remove(0);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (const std::out_of_range &error)
  {
    std::cerr << error.what();
    return 1;
  }
  std::cout << "After removing: ";
  compositeShape.print(std::cout);
return 0;
}

void demonstrateFunctionShape(korzh::Shape* shape)
{
  shape->print(std::cout);
  const double COEFFICIENT = 2.0;
  shape->scale(COEFFICIENT);
  std::cout << "Shape after scaling: ";
  shape->print(std::cout);
}

void demonstrateFunctionCompositeShape(korzh::CompositeShape& compositeShape)
{
  std::cout << "Output of a CompositeShape\n";
  compositeShape.print(std::cout);
  std::cout << compositeShape.getSize() << '\n';
  std::cout << "The area of all shapes\n";
  std::cout << compositeShape.getArea() << '\n';

  const double DX = 5.0;
  const double DY = 10.0;
  compositeShape.move(DX, DY);
  compositeShape.print(std::cout);

  const korzh::point_t DELTA = {567.12, 622.55};
  compositeShape.move(DELTA);
  compositeShape.print(std::cout);

  const double COEFFICIENT = 2.0;
  compositeShape.scale(COEFFICIENT);
  std::cout << "After scaling: ";
  compositeShape.print(std::cout);

  std::cout << "Frame CompositeShape: " << compositeShape.getFrameRect().width
            << ", " << compositeShape.getFrameRect().height << " Positions: "
            << compositeShape.getFrameRect().pos.x << ", " << compositeShape.getFrameRect().pos.y << '\n';
}
