// C++ Boost unit tests for SymbolicFactory.hpp
#define BOOST_TEST_DYN_LINK
//#define BOOST_ALL_NO_LIB
#include <boost/test/unit_test.hpp>
//#include <boost/test/tools/output_test_stream.hpp>

#include "SymbolicFactory.hpp"

using namespace winglib;

DECLARE_SYMBOLIC(test)
public:
    test() = default;
    virtual ~test() = default;
};
IMPLEMENT_SYMBOLIC(test);

BOOST_AUTO_TEST_SUITE(SymbolicFactoryTest)

// Test getSymbolic() with valid symbol
BOOST_AUTO_TEST_CASE(getSymbolicWithValidSymbol)
{
    // Get singleton factory instance
    SymbolicFactory *factory = SymbolicFactory::getInstance();

    // Create a Symbolic object
    //SymbolicBase *symbol = new Symbolic("test");

    // Add the symbol to the factory map
    //factory->registerSymbol("test", symbol);

    // Get the symbol from the factory
    SymbolicBase *result = factory->getSymbolic("test", nullptr);

    // Check that the symbols are equal
    //BOOST_CHECK_EQUAL(symbol, result);
    BOOST_TEST(result);
}

// Test getSymbolic() with invalid symbol
BOOST_AUTO_TEST_CASE(getSymbolicWithInvalidSymbol)
{
    // Get singleton factory instance
    SymbolicFactory *factory = SymbolicFactory::getInstance();

    std::function<bool(const std::exception &)> fp = [](const std::exception &e) {
        return e.what() == std::string("Unexpected symbol name : invalid");
    };

    // Get the symbol from the factory
    BOOST_CHECK_EXCEPTION(factory->getSymbolic("invalid", nullptr), std::runtime_error, fp);
    
}

BOOST_AUTO_TEST_SUITE_END()