#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(CircleTest)

struct fixture
{
  const double EPSILON = 0.0001;
  const double TEST_RADIUS = 3.1;
  const double x = 22.2;
  const double y = 65.1;
  const double TEST_DX = 2.1;
  const double TEST_DY = 1.2;
  const double TEST_INVALID_VALUE = -2.0;
  const double TEST_COEFFICIENT = 2.0;
  const korzh::point_t TEST_POSITION = {22.2,65.1};
  korzh::Circle figure;

  fixture():
    figure(TEST_POSITION, TEST_RADIUS)
  {}
};

BOOST_FIXTURE_TEST_CASE(checkCorrectGettersCircle, fixture)
{
  BOOST_CHECK_CLOSE(figure.getRadius(), TEST_RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(figure.getArea(), TEST_RADIUS * TEST_RADIUS * M_PI, EPSILON);
  const korzh::rectangle_t value = figure.getFrameRect();
  BOOST_CHECK_CLOSE(value.height, TEST_RADIUS + TEST_RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(value.width, TEST_RADIUS + TEST_RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(value.pos.x, x, EPSILON);
  BOOST_CHECK_CLOSE(value.pos.y, y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(checkTheImmutabilityOfRadius, fixture)
{
  const double radiusBefore = figure.getRadius();
  figure.move(TEST_DX, TEST_DY);
  const double radiusAfter = figure.getRadius();
  BOOST_CHECK_CLOSE(radiusBefore, radiusAfter, EPSILON);
  figure.move(TEST_POSITION);
  const double radiusAfterTwo = figure.getRadius();
  BOOST_CHECK_CLOSE(radiusAfter, radiusAfterTwo, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(checkTheImmutabilityOfWidth, fixture)
{
  const double widthBefore = figure.getFrameRect().width;
  figure.move(TEST_DX, TEST_DY);
  const double widthAfter = figure.getFrameRect().width;
  BOOST_CHECK_CLOSE(widthBefore, widthAfter, EPSILON);
  figure.move(TEST_POSITION);
  const double widthAfterTwo = figure.getFrameRect().width;
  BOOST_CHECK_CLOSE(widthAfter, widthAfterTwo, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(checkTheImmutabilityOfHeight, fixture)
{
  const double heightBefore = figure.getFrameRect().height;
  figure.move(TEST_DX, TEST_DY);
  const double heightAfter = figure.getFrameRect().height;
  BOOST_CHECK_CLOSE(heightBefore, heightAfter, EPSILON);
  figure.move(TEST_POSITION);
  const double heightAfterTwo = figure.getFrameRect().height;
  BOOST_CHECK_CLOSE(heightAfter, heightAfterTwo, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(Area, fixture)
{
  BOOST_CHECK_CLOSE(TEST_RADIUS * TEST_RADIUS * M_PI, figure.getArea(), EPSILON);
}

BOOST_FIXTURE_TEST_CASE(AreasValidationAfterMove, fixture)
{
  const double areaBefore = figure.getArea();
  figure.move(TEST_DX, TEST_DY);
  const double areaAfter = figure.getArea();
  BOOST_CHECK_CLOSE(areaBefore, areaAfter, EPSILON);
  const double areaAfterTwo = figure.getArea();
  BOOST_CHECK_CLOSE(areaAfter, areaAfterTwo, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(QuadraticChangeArea, fixture)
{
  const double areaBefore = figure.getArea();
  figure.scale(TEST_COEFFICIENT);
  const double areaAfter = figure.getArea();
  BOOST_CHECK_CLOSE(areaBefore * TEST_COEFFICIENT * TEST_COEFFICIENT, areaAfter, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().width, 2.0 * TEST_RADIUS * TEST_COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().height, 2.0 * TEST_RADIUS * TEST_COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().pos.x, x, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().pos.y, y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(InvalidParametersInFunction, fixture)
{
  BOOST_CHECK_THROW(korzh::Circle figure(TEST_POSITION, -TEST_RADIUS), std::invalid_argument);
  BOOST_CHECK_THROW(korzh::Circle figure(TEST_POSITION, 0.0), std::invalid_argument);
  BOOST_CHECK_THROW(figure.scale(TEST_INVALID_VALUE), std::invalid_argument);
  BOOST_CHECK_THROW(figure.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
