#include <iostream>
#include <sstream>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "shape.hpp"

BOOST_AUTO_TEST_SUITE(test_shape)

struct Fixture
{
  const Shape triangle = {{1, 2}, {4, 5}, {7, 1}};
  const Shape rectangle = {{2, 1}, {2, 4}, {7, 4}, {7, 1}};
  const Shape square = {{1, 1}, {1, 4}, {4, 4}, {4, 1}};
  const Shape pentagon = {{2, 1}, {2, 4}, {4, 5}, {4, 6}, {4, 1}};

  Shape shape;
  Point point;
  std::istringstream input;
  std::ostringstream out;
};

BOOST_FIXTURE_TEST_CASE(ValidComparator, Fixture)
{
  ShapesComparator comparator;
  BOOST_CHECK(comparator(triangle, rectangle));
  BOOST_CHECK(comparator(triangle, square));
  BOOST_CHECK(comparator(square, pentagon));
  BOOST_CHECK(comparator(rectangle, pentagon));
  BOOST_CHECK(comparator(triangle, pentagon));
}

BOOST_FIXTURE_TEST_CASE(ValidWorkWithPoint, Fixture)
{
  input.str("(23;-656)");
  input >> point;
  BOOST_CHECK_EQUAL(point.x, 23);
  BOOST_CHECK_EQUAL(point.y, -656);
  out << point;
  BOOST_CHECK_EQUAL(out.str(), "(23;-656)");
}

BOOST_FIXTURE_TEST_CASE(ValidWorkWithShape, Fixture)
{
  input.str("4 (1;1) (1;4) (3;1) (3;4)");
  input >> shape;
  BOOST_CHECK_EQUAL(shape.size(), 4);
  BOOST_CHECK_EQUAL(shape[0].x, 1);
  BOOST_CHECK_EQUAL(shape[0].y, 1);
  BOOST_CHECK_EQUAL(shape[1].x, 1);
  BOOST_CHECK_EQUAL(shape[1].y, 4);
  BOOST_CHECK_EQUAL(shape[2].x, 3);
  BOOST_CHECK_EQUAL(shape[2].y, 1);
  BOOST_CHECK_EQUAL(shape[3].x, 3);
  BOOST_CHECK_EQUAL(shape[3].y, 4);

  out << shape;
  BOOST_CHECK_EQUAL(out.str(), "4 (1;1) (1;4) (3;1) (3;4) ");
}

BOOST_FIXTURE_TEST_CASE(ValidCheckTypeOfShapes, Fixture)
{
  BOOST_CHECK(isTriangle(triangle));
  BOOST_CHECK(!isTriangle(rectangle));
  BOOST_CHECK(!isTriangle(square));
  BOOST_CHECK(!isTriangle(pentagon));

  BOOST_CHECK(isRectangle(rectangle));
  BOOST_CHECK(isRectangle(square));
  BOOST_CHECK(!isRectangle(triangle));
  BOOST_CHECK(!isRectangle(pentagon));

  BOOST_CHECK(isSquare(square));
  BOOST_CHECK(!isSquare(triangle));
  BOOST_CHECK(!isSquare(rectangle));
  BOOST_CHECK(!isSquare(pentagon));

  BOOST_CHECK(isPentagon(pentagon));
  BOOST_CHECK(!isPentagon(triangle));
  BOOST_CHECK(!isPentagon(rectangle));
  BOOST_CHECK(!isPentagon(square));
}

BOOST_FIXTURE_TEST_CASE(InvalidWorkWithPoint, Fixture)
{
  input.str("(;-656)");
  input >> point;
  BOOST_CHECK(!input);
  input.clear();

  input.str("(23;)");
  input >> point;
  BOOST_CHECK(!input);
  input.clear();

  input.str("(23 -55)");
  input >> point;
  BOOST_CHECK(!input);
  input.clear();

  input.str("23;-55)");
  input >> point;
  BOOST_CHECK(!input);
  input.clear();

  input.str("(23;-55");
  input >> point;
  BOOST_CHECK(!input);
  input.clear();

  input.str("23;-55");
  input >> point;
  BOOST_CHECK(!input);
}

BOOST_FIXTURE_TEST_CASE(ValidGetQuadraticDistance, Fixture)
{
  BOOST_CHECK(getQuadraticDistance(triangle[0], triangle[1])
      == std::pow((triangle[1].x - triangle[0].x), 2) + std::pow((triangle[1].y - triangle[0].y), 2));
  BOOST_CHECK(getQuadraticDistance(square[0], square[1])
      == std::pow((square[1].x - square[0].x), 2) + std::pow((square[1].y - square[0].y), 2));
  BOOST_CHECK(getQuadraticDistance(rectangle[0], rectangle[1])
      == std::pow((rectangle[1].x - rectangle[0].x), 2) + std::pow((rectangle[1].y - rectangle[0].y), 2));
}

BOOST_FIXTURE_TEST_CASE(InvalidWorkWithShape, Fixture)
{
  input.str("4 (1;1) (1;4) (3;4)");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("4 (1;1) (1;4) (3;1) (3;4) (3;4)");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("-4 (1;1) (1;4) (3;1) (3;4)");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("-4");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("0");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("3 sdopds");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("");
  input >> shape;
  BOOST_CHECK(!input);
  input.clear();

  input.str("dsp[psas(do/ewdqof]wq/dswqpx,d)");
  input >> shape;
  BOOST_CHECK(!input);
}

BOOST_AUTO_TEST_SUITE_END()
