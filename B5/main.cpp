#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <list>
#include <algorithm>
#include <unordered_set>
#include "shape.hpp"

void taskOne(std::istream& input, std::ostream& out);
void taskTwo(std::istream& input, std::ostream& out);

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid count of arguments";
    return 1;
  }
  size_t taskNum = 0;
  std::istringstream stream(argv[1]);
  stream >> taskNum;
  if (!stream.eof())
  {
    std::cerr << "Error when reading argument from a stream";
    return 1;
  }
  if ((taskNum < 1) || (taskNum > 2))
  {
    std::cerr << "Invalid number of task";
    return 1;
  }
  if (taskNum == 1)
  {
    try
    {
      taskOne(std::cin, std::cout);
    }
    catch (std::exception &error)
    {
      std::cerr << error.what();
      return 2;
    }
  }
  if (taskNum == 2)
  {
    try
    {
      taskTwo(std::cin, std::cout);
    }
    catch (std::exception &error)
    {
      std::cerr << error.what();
      return 2;
    }
  }
  return 0;
}

void taskOne(std::istream& input, std::ostream& out)
{
  std::unordered_set<std::string> unique_words ((std::istream_iterator<std::string>(input)),
      std::istream_iterator<std::string>());
  if (!input.eof())
  {
    throw std::runtime_error("Reading error");
  }
  std::copy(unique_words.begin(), unique_words.end(),
      std::ostream_iterator<std::string>(out, "\n"));
}

void taskTwo(std::istream& input, std::ostream& out)
{
  std::list<Shape> shapes((std::istream_iterator<Shape>(input)), std::istream_iterator<Shape>());
  if (!input.eof())
  {
    throw std::runtime_error("Reading error");
  }
  size_t vertices = 0;
  std::for_each(shapes.begin(), shapes.end(),
      [&](const Shape& shape)
        {
          vertices += shape.size();
        });
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), &isPentagon), shapes.end());
  const size_t numTriangles = std::count_if(shapes.begin(), shapes.end(), &isTriangle);
  const size_t numSquares = std::count_if(shapes.begin(), shapes.end(), &isSquare);
  const size_t numRectangles = std::count_if(shapes.begin(), shapes.end(), &isRectangle);

  std::vector<Point> points_shape;
  points_shape.reserve(shapes.size());
  std::for_each(shapes.begin(), shapes.end(),
      [&](const Shape& shape)
      {
        points_shape.push_back(shape.front());
      });
  shapes.sort(ShapesComparator());
  out << "Vertices: " << vertices << "\nTriangles: " << numTriangles << "\nSquares: "
      << numSquares << "\nRectangles: "<< numRectangles << "\nPoints: ";
  std::copy(points_shape.begin(), points_shape.end(), std::ostream_iterator<Point>(out, " "));
  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
