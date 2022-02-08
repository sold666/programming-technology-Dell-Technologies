#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(RectangleTest)

struct fixture
{
  const double EPSILON = 0.0001;
  const double TEST_WIDTH = 6.09;
  const double TEST_HEIGHT = 6.09;
  const double x = 22.2;
  const double y = 65.1;
  const double TEST_DX = 2.1;
  const double TEST_DY = 1.2;
  const double TEST_INVALID_VALUE = -2.0;
  const double TEST_COEFFICIENT = 2.0;
  const korzh::point_t TEST_POSITION = {22.2,65.1};
  korzh::Rectangle figure;

  fixture():
    figure(TEST_POSITION, TEST_WIDTH, TEST_HEIGHT)
  {}
};

BOOST_FIXTURE_TEST_CASE(checkCorrectGettersRectangle, fixture)
{
  BOOST_CHECK_CLOSE(figure.getArea(), TEST_WIDTH * TEST_HEIGHT, EPSILON);
  const korzh::rectangle_t value = figure.getFrameRect();
  BOOST_CHECK_CLOSE(value.width, TEST_WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(value.height, TEST_HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(value.pos.x, x, EPSILON);
  BOOST_CHECK_CLOSE(value.pos.y, y, EPSILON);
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

BOOST_FIXTURE_TEST_CASE(Area, fixture)
{
  BOOST_CHECK_CLOSE(TEST_WIDTH * TEST_HEIGHT, figure.getArea(), EPSILON);
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
  BOOST_CHECK_CLOSE(areaBefore * TEST_COEFFICIENT * TEST_COEFFICIENT, areaAfter, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().width, TEST_WIDTH * TEST_COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().height, TEST_HEIGHT * TEST_COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().pos.x, x, EPSILON);
  BOOST_CHECK_CLOSE(figure.getFrameRect().pos.y, y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(InvalidParametersInFunction, fixture)
{
  BOOST_CHECK_THROW(korzh::Rectangle figure(TEST_POSITION, -TEST_WIDTH, -TEST_HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(korzh::Rectangle figure(TEST_POSITION, 0.0, 0.0), std::invalid_argument);
  BOOST_CHECK_THROW(figure.scale(TEST_INVALID_VALUE), std::invalid_argument);
  BOOST_CHECK_THROW(figure.scale(0.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
