#define BOOST_TEST_MODULE S1
#include <boost/test/included/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(ListTests)

BOOST_AUTO_TEST_CASE(pushFront_empty)
{
  madieva::List< int > list;
  BOOST_CHECK(list.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(pushFront)
{
  madieva::List< int > list;
  list.pushFront(10);
  list.pushFront(20);
  list.pushFront(30);
  list.pushFront(40);
  BOOST_CHECK(list.getSize() == 4);

  auto it = list.begin();
  BOOST_CHECK(*it == 40);
  ++it;
  BOOST_CHECK(*it == 30);
  ++it;
  BOOST_CHECK(*it == 20);
  ++it;
  BOOST_CHECK(*it == 10);
}

BOOST_AUTO_TEST_CASE(pushBack)
{
  madieva::List< int > list;
  list.pushBack(10);
  list.pushBack(20);
  list.pushBack(30);
  list.pushBack(40);
  BOOST_CHECK(list.getSize() == 4);

  auto it = list.begin();
  BOOST_CHECK(*it == 10);
  ++it;
  BOOST_CHECK(*it == 20);
  ++it;
  BOOST_CHECK(*it == 30);
  ++it;
  BOOST_CHECK(*it == 40);
}

BOOST_AUTO_TEST_CASE(popFront)
{
  madieva::List<int> list;
  list.pushBack(10);
  list.pushBack(20);
  list.pushBack(30);

  list.popFront();
  BOOST_CHECK(list.getSize() == 2);
  auto it = list.begin();
  BOOST_CHECK(*it == 20);
  ++it;
  BOOST_CHECK(*it == 30);
}

BOOST_AUTO_TEST_CASE(popBack)
{
  madieva::List<int> list;
  list.pushBack(10);
  list.pushBack(20);
  list.pushBack(30);

  list.popBack();
  BOOST_CHECK(list.getSize() == 2);
  auto it = list.begin();
  BOOST_CHECK(*it == 10);
  ++it;
  BOOST_CHECK(*it == 20);
}

BOOST_AUTO_TEST_CASE(popBack_one)
{
  madieva::List<int> list;
  list.pushBack(10);
  list.popBack();
  BOOST_CHECK(list.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(popFront_one)
{
  madieva::List<int> list;
  list.pushFront(10);
  list.popFront();
  BOOST_CHECK(list.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(clear)
{
  madieva::List<int> list;
  list.pushBack(1);
  list.pushBack(2);
  list.pushBack(3);
  list.clear();
  BOOST_CHECK(list.getSize() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
