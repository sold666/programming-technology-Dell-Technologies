#include <memory>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"


BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

struct fixture
{
  const double EPSILON = 0.0001;
  const double TEST_RADIUS = 5.0;
  const double TEST_WIDTH = 10.0;
  const double TEST_HEIGHT = 10.0;
  const double TEST_DX = 52.1;
  const double TEST_DY = -21.2;
  const double TEST_INVALID_VALUE = -2.0;
  const double TEST_COEFFICIENT = 2.0;
  const double SIZE = 2.0;
  const korzh::point_t TEST_POSITION = {20.0,65.0};
  const korzh::point_t NEW_TEST_POSITION = {10.2, 75.1};

  korzh::CompositeShape compositeShape;
  const std::shared_ptr<korzh::Shape> circle = std::make_shared<korzh::Circle>(TEST_POSITION, TEST_RADIUS);
  const std::shared_ptr<korzh::Shape> rectangle = std::make_shared<korzh::Rectangle>(TEST_POSITION, TEST_WIDTH, TEST_HEIGHT);

  fixture()
  {
    compositeShape.add(rectangle);
    compositeShape.add(circle);
  }
};

BOOST_FIXTURE_TEST_CASE(emptyGetFrameRect, fixture)
{
  korzh::CompositeShape emptyCompShape;
  std::shared_ptr<korzh::Shape> emptyShape(std::make_shared<korzh::CompositeShape>());
  emptyCompShape.add(emptyShape);
  const korzh::rectangle_t frameRect = emptyCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.width, 0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, 0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.x, 0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y, 0, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(getFrameRectWithFirstEmptyComponent, fixture)
{
  korzh::CompositeShape emptyCompShape;
  std::shared_ptr<korzh::Shape> emptyShape1(std::make_shared<korzh::CompositeShape>());
  std::shared_ptr<korzh::Shape> emptyShape2(std::make_shared<korzh::CompositeShape>());
  emptyCompShape.add(emptyShape1);
  emptyCompShape.add(emptyShape2);
  emptyCompShape.add(circle);
  const korzh::rectangle_t frameRect = emptyCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.width, circle->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, circle->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.x, circle->getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y, circle->getFrameRect().pos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(getFrameRectWithMiddleEmptyComponent, fixture)
{
  korzh::CompositeShape emptyCompShape;
  std::shared_ptr<korzh::Shape> emptyShape(std::make_shared<korzh::CompositeShape>());
  emptyCompShape.add(circle);
  emptyCompShape.add(emptyShape);
  emptyCompShape.add(rectangle);
  const korzh::rectangle_t frameRect = emptyCompShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.width, circle->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, circle->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.x, circle->getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y, circle->getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.width, rectangle->getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, rectangle->getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.x, rectangle->getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y, rectangle->getFrameRect().pos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(checkCorrectGettersCompositeShape, fixture)
{
  BOOST_CHECK_CLOSE(compositeShape.getArea(), rectangle->getArea() + circle->getArea(), EPSILON);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), SIZE);
  const korzh::rectangle_t value = compositeShape.getFrameRect();
  const double compositeShapeWidth = (TEST_RADIUS * 2 + TEST_WIDTH) / 2;
  const double compositeShapeHeight = TEST_RADIUS * 2;
  const double compositeShapeX = (compositeShape[0]->getFrameRect().pos.x + compositeShape[1]->getFrameRect().pos.x) / 2;
  const double compositeShapeY = (compositeShape[0]->getFrameRect().pos.y + compositeShape[1]->getFrameRect().pos.y) / 2;
  BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  BOOST_CHECK_CLOSE(compositeShapeWidth, value.width, EPSILON);
  BOOST_CHECK_CLOSE(compositeShapeHeight, value.height, EPSILON);
  BOOST_CHECK_CLOSE(compositeShapeX, value.pos.x, EPSILON);
  BOOST_CHECK_CLOSE(compositeShapeY, value.pos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(checkCorrectCompositeShape, fixture)
{
  BOOST_REQUIRE_EQUAL(compositeShape[1], circle);
  BOOST_REQUIRE_EQUAL(compositeShape[0], rectangle);
}

BOOST_FIXTURE_TEST_CASE(checkCorrectConstuctors, fixture)
{
  korzh::CompositeShape copy(compositeShape);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), copy.getSize());
  for (size_t i = 0; i < compositeShape.getSize(); ++i)
  {
    BOOST_CHECK_EQUAL(compositeShape[i], copy[i]);
  }

  korzh::CompositeShape moved(std::move(copy));
  BOOST_CHECK_EQUAL(moved.getSize(), compositeShape.getSize());
  BOOST_CHECK_EQUAL(copy.getSize(), 0);
  for (size_t i = 0; i < compositeShape.getSize(); ++i)
  {
    BOOST_CHECK_EQUAL(compositeShape[i], moved[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(EmptyParameterInCopyConstructor, fixture)
{
  korzh::CompositeShape emptyShape;
  BOOST_CHECK_NO_THROW(korzh::CompositeShape copy(emptyShape));
  korzh::CompositeShape copy(emptyShape);
  BOOST_CHECK_EQUAL(copy.getSize(), 0);
}

BOOST_FIXTURE_TEST_CASE(EmptyParameterInMoveConstructor, fixture)
{
  korzh::CompositeShape emptyShape;
  BOOST_CHECK_NO_THROW(korzh::CompositeShape moved(std::move(emptyShape)));
  korzh::CompositeShape moved(std::move(emptyShape));
  BOOST_CHECK_EQUAL(moved.getSize(), 0);
}

BOOST_FIXTURE_TEST_CASE(AssignmentOperators, fixture)
{
  korzh::CompositeShape copy = compositeShape;
  BOOST_CHECK_EQUAL(compositeShape.getSize(), copy.getSize());
  for (size_t i = 0; i < compositeShape.getSize(); ++i) {
    BOOST_CHECK_EQUAL(compositeShape[i], copy[i]);
  }

  korzh::CompositeShape moved = std::move(copy);
  BOOST_CHECK_EQUAL(moved.getSize(), compositeShape.getSize());
  BOOST_CHECK_EQUAL(copy.getSize(), 0);
  for (size_t i = 0; i < compositeShape.getSize(); ++i)
  {
    BOOST_CHECK_EQUAL(compositeShape[i], moved[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(GetFrameRectValidationAfterMove, fixture)
{
  const korzh::rectangle_t frameRect = compositeShape.getFrameRect();
  compositeShape.move(TEST_DX, TEST_DY);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.x + TEST_DX, compositeShape.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y + TEST_DY, compositeShape.getFrameRect().pos.y, EPSILON);
  compositeShape.move(NEW_TEST_POSITION);
  BOOST_CHECK_CLOSE(frameRect.width, compositeShape.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, compositeShape.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(NEW_TEST_POSITION.x, compositeShape.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(NEW_TEST_POSITION.y, compositeShape.getFrameRect().pos.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(CheckForFrameRectMovePosChanges, fixture)
{
  const korzh::rectangle_t frameRect = compositeShape.getFrameRect();
  const korzh::rectangle_t rectOneBefore = compositeShape[0]->getFrameRect();
  const korzh::rectangle_t rectTwoBefore = compositeShape[1]->getFrameRect();
  compositeShape.scale(TEST_COEFFICIENT);
  const korzh::rectangle_t rectOneAfter = compositeShape[0]->getFrameRect();
  const korzh::rectangle_t rectTwoAfter = compositeShape[1]->getFrameRect();

  BOOST_CHECK_CLOSE(rectOneAfter.pos.x, frameRect.pos.x + TEST_COEFFICIENT * (rectOneBefore.pos.x - frameRect.pos.x), EPSILON);
  BOOST_CHECK_CLOSE(rectOneAfter.pos.y, frameRect.pos.y + TEST_COEFFICIENT * (rectOneBefore.pos.y - frameRect.pos.y), EPSILON);
  BOOST_CHECK_CLOSE(rectTwoAfter.pos.x, frameRect.pos.x + TEST_COEFFICIENT * (rectTwoBefore.pos.x - frameRect.pos.x), EPSILON);
  BOOST_CHECK_CLOSE(rectTwoAfter.pos.y, frameRect.pos.y + TEST_COEFFICIENT * (rectTwoBefore.pos.y - frameRect.pos.y), EPSILON);
}

BOOST_FIXTURE_TEST_CASE(EmptyGetFrameRect, fixture)
{
  korzh::CompositeShape emptyComponentsShape;
  std::shared_ptr<korzh::CompositeShape> emptyShape(std::make_shared<korzh::CompositeShape>());
  emptyComponentsShape.add(emptyShape);
  const korzh::rectangle_t frameRect = emptyComponentsShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRect.width, 0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.height, 0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.x, 0, EPSILON);
  BOOST_CHECK_CLOSE(frameRect.pos.y, 0, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(AreasValidationAfterMove, fixture)
{
  const double areaBefore = compositeShape.getArea();
  compositeShape.move(TEST_DX, TEST_DY);
  const double areaAfter = compositeShape.getArea();
  BOOST_CHECK_CLOSE(areaBefore, areaAfter, EPSILON);
  compositeShape.move(TEST_POSITION);
  const double areaAfterTwo = compositeShape.getArea();
  BOOST_CHECK_CLOSE(areaAfter, areaAfterTwo, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(QuadraticChangeArea, fixture)
{
  const double areaBefore = compositeShape.getArea();
  const double frameHeight = compositeShape.getFrameRect().height;
  const double frameWidth = compositeShape.getFrameRect().width;
  const double framePosX = compositeShape.getFrameRect().pos.x;
  const double framePosY = compositeShape.getFrameRect().pos.y;
  compositeShape.scale(TEST_COEFFICIENT);
  const double areaAfter = compositeShape.getArea();
  BOOST_CHECK_CLOSE(areaBefore * TEST_COEFFICIENT * TEST_COEFFICIENT, areaAfter, EPSILON);
  BOOST_CHECK_CLOSE(areaBefore * TEST_COEFFICIENT * TEST_COEFFICIENT, areaAfter, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameWidth * TEST_COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameHeight * TEST_COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, framePosX, EPSILON);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, framePosY, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(ValidIndex, fixture)
{
  BOOST_CHECK_EQUAL(compositeShape[1], circle);
  BOOST_CHECK_EQUAL(compositeShape[0], rectangle);
}

BOOST_FIXTURE_TEST_CASE(InvalidIndex, fixture)
{
  BOOST_CHECK_THROW(compositeShape[2], std::out_of_range);
  BOOST_CHECK_THROW(compositeShape[-2], std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(ScaleInvalidArguments, fixture)
{
  BOOST_CHECK_THROW(compositeShape.scale(TEST_INVALID_VALUE), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.scale(0), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(InvalidParametersInFunction, fixture)
{
  std::shared_ptr<korzh::CompositeShape> compositeShapePtr(std::make_shared<korzh::CompositeShape>());
  BOOST_CHECK_THROW(compositeShapePtr->add(compositeShapePtr), std::logic_error);

  std::shared_ptr<korzh::Shape> emptyShape(nullptr);
  BOOST_CHECK_THROW(compositeShape.add(emptyShape), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.add(circle),  std::logic_error);
  BOOST_CHECK_THROW(compositeShape.add(rectangle),  std::logic_error);

  BOOST_CHECK_NO_THROW(compositeShape.remove(1));
  BOOST_CHECK_THROW(compositeShape[1], std::out_of_range);
  BOOST_CHECK_THROW(compositeShape.remove(4), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
