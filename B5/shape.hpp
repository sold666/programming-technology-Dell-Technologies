#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <iosfwd>
#include <vector>

struct Point
{
  int x, y;
};

using Shape = std::vector<Point>;

struct ShapesComparator
{
  bool operator()(const Shape& shape_one, const Shape& shape_two) const;
};

std::istream& operator>>(std::istream& input, Point& point);
std::istream& operator>>(std::istream& input, Shape& shape);
std::ostream& operator<<(std::ostream& out, const Point& point);
std::ostream& operator<<(std::ostream& out, const Shape& shape);

size_t getQuadraticDistance(const Point& point_first, const Point& point_second);

bool isTriangle(const Shape& shape);
bool isSquare(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isPentagon(const Shape& shape);

#endif
