#include <boost/test/unit_test.hpp>
#include "bstree.hpp"
#include "tree_iterator.hpp"

BOOST_AUTO_TEST_SUITE(BSTreeRotateTest)

BOOST_AUTO_TEST_CASE(key_value)
{
  madieva::BSTree< int, std::string, std::less< int > > tree;
  tree.push(10, "a");
  tree.push(20, "b");
  tree.push(15, "c");

  madieva::TIter< int, std::string, std::less< int > > it = tree.begin();
  BOOST_CHECK((*it).first == 10);
  BOOST_CHECK((*it).second == "a");
  ++it;
  BOOST_CHECK((*it).first == 15);
  BOOST_CHECK((*it).second == "b");
  ++it;
  BOOST_CHECK((*it).first == 20);
  BOOST_CHECK((*it).second == "c");

}

BOOST_AUTO_TEST_CASE(repeat_key_push)
{
  madieva::BSTree< int, std::string, std::less< int > > tree;
  tree.push(10, "a");
  tree.push(10, "b");
  tree.push(15, "c");

  madieva::TIter< int, std::string, std::less< int > > it = tree.begin();
  size_t count = 0;
  for (; it != tree.end(); ++it) {
    count++;
  }
  BOOST_CHECK(count == 2);
  madieva::TIter< int, std::string, std::less< int > > it1 = tree.begin();
  BOOST_CHECK((*it1).first == 10);
  BOOST_CHECK((*it1).second == "a");

  BOOST_CHECK((*it1).first == 15);
  BOOST_CHECK((*it1).second == "c");

}

BOOST_AUTO_TEST_CASE(rotate_left_simple)
{
  madieva::BSTree< int, std::string, std::less< int > > tree;
  tree.push(10, "a");
  tree.push(20, "b");
  tree.push(15, "c");

  madieva::TIter< int, std::string, std::less< int > > it1 = tree.begin();
  madieva::TIter< int, std::string, std::less< int > > it2 = tree.begin();
  ++it2;
  madieva::TIter< int, std::string, std::less< int > > it3 = tree.begin();
  ++it3;
  ++it3;

  tree.rotateLeft(it1);

  madieva::TIter< int, std::string, std::less< int > > r_it1 = tree.begin();
  madieva::TIter< int, std::string, std::less< int > > r_it2 = tree.begin();
  ++r_it2;
  madieva::TIter< int, std::string, std::less< int > > r_it3 = tree.begin();
  ++r_it3;
  ++r_it3;
  BOOST_CHECK(it1 == r_it1 && it2 == r_it2 && it3 == r_it3);
}

BOOST_AUTO_TEST_CASE(rotate__right_simple)
{
  madieva::BSTree< int, std::string, std::less< int > > tree;
  tree.push(10, "a");
  tree.push(5, "b");
  tree.push(7, "c");

  madieva::TIter< int, std::string, std::less< int > > it1 = tree.begin();
  madieva::TIter< int, std::string, std::less< int > > it2 = tree.begin();
  ++it2;
  madieva::TIter< int, std::string, std::less< int > > it3 = tree.begin();
  ++it3;
  ++it3;

  tree.rotateRight(it1);

  madieva::TIter< int, std::string, std::less< int > > r_it1 = tree.begin();
  madieva::TIter< int, std::string, std::less< int > > r_it2 = tree.begin();
  ++r_it2;
  madieva::TIter< int, std::string, std::less< int > > r_it3 = tree.begin();
  ++r_it3;
  ++r_it3;
  BOOST_CHECK(it1 == r_it1 && it2 == r_it2 && it3 == r_it3);
}


BOOST_AUTO_TEST_SUITE_END()
