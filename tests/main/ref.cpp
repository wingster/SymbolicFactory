#include <boost/test/unit_test.hpp>

// Reference code to check if the boost unit test setup is proper - version upgrades...etc
// Addtional information for boost unit test framework can be found under :
// https://www.boost.org/doc/libs/1_82_0/libs/test/doc/html/boost_test/intro.html
// https://www.boost.org/doc/libs/1_49_0/libs/test/doc/html/tutorials/new-year-resolution.html
// https://chuckaknight.wordpress.com/2013/04/18/testing-using-the-boost-unit-test-framework/

BOOST_AUTO_TEST_CASE(boost_framework_test)
{
  int i = 1;
  BOOST_TEST(i == 1);
}