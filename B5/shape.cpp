#include "shape.hpp"
#include <iostream>
#include <boost/io/ios_state.hpp>
#include "utility.hpp"

const char OPENING_BRACE = '(';
const char SEPARATOR = ';';
const char CLOSING_BRACE = ')';
const unsigned int TRIANGLE_SIZE = 3;
const unsigned int QUADRILATERAL_SIZE = 4;
const unsigned int PENTAGON_SIZE = 5;

std::istream& operator>>(std::istream& input, Shape& shape)
{
  boost::io::ios_flags_saver saver(input);
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  int vertices;
  if (!(input >> std::noskipws >> std::ws >> vertices) || (vertices <= 0))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  Shape temp_shape(vertices);
  for (auto& i : temp_shape)
  {
    if (!(input >> skipWS >> i))
    {
      return input;
    }
  }
  input >> skipWS;
  if (!input.eof() && (input.peek() != '\r') && (input.peek() != '\n'))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  shape = std::move(temp_shape);
  return input;
}

std::istream &operator>>(std::istream &input, Point &point)
{
  boost::io::ios_flags_saver saver(input);
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  char symbol;
  if (!(input >> std::noskipws >> skipWS >> symbol) || (symbol != OPENING_BRACE))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  int x;
  if (!(input >> skipWS >> x >> skipWS >> symbol) || (symbol != SEPARATOR))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  int y;
  if (!(input >> skipWS >> y >> skipWS >> symbol) || (symbol != CLOSING_BRACE))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  point = {x, y};
  return input;
}

std::ostream &operator<<(std::ostream &out, const Point &point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << OPENING_BRACE << point.x << SEPARATOR
      << point.y << CLOSING_BRACE;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << shape.size() << ' ';
  for (auto i : shape)
  {
    out << i << " ";
  }
  return out;
}

bool ShapesComparator::operator()(const Shape& shape_one, const Shape& shape_two) const
{
  if ((shape_one.size() == QUADRILATERAL_SIZE) && (shape_two.size() == QUADRILATERAL_SIZE))
  {
    return isSquare(shape_one) && !isSquare(shape_two);
  }
  return shape_one.size() < shape_two.size();
}

size_t getQuadraticDistance(const Point &point_first, const Point &point_second)
{
  return (point_first.x - point_second.x) * (point_first.x - point_second.x)
      + (point_first.y - point_second.y) * (point_first.y - point_second.y);
}

bool isTriangle(const Shape &shape)
{
  return shape.size() == TRIANGLE_SIZE;
}

bool isSquare(const Shape &shape)
{
  const size_t firstSideSquared = getQuadraticDistance(shape[0], shape[1]);
  const size_t secondSideSquared = getQuadraticDistance(shape[1], shape[2]);
  return isRectangle(shape) && (firstSideSquared == secondSideSquared);
}

bool isRectangle(const Shape &shape)
{
  return shape.size() == QUADRILATERAL_SIZE;
}

bool isPentagon(const Shape &shape)
{
  return shape.size() == PENTAGON_SIZE;
}
