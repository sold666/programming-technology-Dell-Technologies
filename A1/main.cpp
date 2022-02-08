#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  const point_t COORDINATE_ONE = {33.2, -332.111};
  const double WIDTH = 2.5;
  const double HEIGHT = 2.5;
  try
  {
    Rectangle figureOne(COORDINATE_ONE, WIDTH, HEIGHT);
    Shape *figureOne_ptr = &figureOne;

    figureOne_ptr->print(std::cout);
    std::cout << "Area: " << figureOne_ptr->getArea() << '\n';
    const double DX = 5;
    const double DY = 10;
    figureOne_ptr->move(DX, DY);
    figureOne_ptr->print(std::cout);
    const point_t DELTA = {567, 622};
    figureOne_ptr->move(DELTA);
    figureOne_ptr->print(std::cout);
    std::cout << "Frame rectangle: " << figureOne_ptr->getFrameRect().width << ", "
              << figureOne_ptr->getFrameRect().height << '\n' << "Positions: "
              << figureOne_ptr->getFrameRect().pos.x << ", " << figureOne_ptr->getFrameRect().pos.y << '\n';
  }
  catch (const std::invalid_argument &error)
  {
    std::cout << error.what();
    return 1;
  }
  const point_t COORDINATE_TWO = {44.2,55.1};
  const double RADIUS = 3;
  try
  {
    Circle figureTwo(COORDINATE_TWO, RADIUS);
    Shape *figureTwo_ptr = &figureTwo;

    figureTwo_ptr->print(std::cout);
    std::cout << "Area: " << figureTwo_ptr->getArea() << '\n';
    const double DX = 5;
    const double DY = 10;
    figureTwo_ptr->move(DX, DY);
    figureTwo_ptr->print(std::cout);
    const point_t DELTA = {124, 255};
    figureTwo_ptr->move(DELTA);
    figureTwo_ptr->print(std::cout);
    std::cout << "Frame rectangle: " << figureTwo_ptr->getFrameRect().width << ", "
              << figureTwo_ptr->getFrameRect().height << '\n' << "Positions: "
              << figureTwo_ptr->getFrameRect().pos.x << ", " << figureTwo_ptr->getFrameRect().pos.y << '\n';
  }
  catch (const std::invalid_argument &error)
  {
    std::cout << error.what();
    return 1;
  }
return 0;
}
