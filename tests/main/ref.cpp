#include <boost/test/unit_test.hpp>

// Reference code to ensure boost unit test works
BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;
  BOOST_TEST(i);
  //BOOST_TEST(i == 2);
}