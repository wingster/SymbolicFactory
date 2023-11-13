#define BOOST_TEST_MODULE SymbolicFactoryTest
#define BOOST_TEST_DYN_LINK
#define BOOST_ALL_NO_LIB
#include <boost/test/included/unit_test.hpp>
#include <boost/core/demangle.hpp>  // to demanagle typeid names

#include "SymbolicFactory.hpp"

////////////////////////////////////////////////////////////////////////////////
// DECLARE Symbolic
DECLARE_SYMBOLIC(SymbolicTest)
public:
    SymbolicTest() = default;
    virtual ~SymbolicTest() = default;
};
IMPLEMENT_SYMBOLIC(SymbolicTest);

DECLARE_SYMBOLIC(DataProviderTest)
public:
    DataProviderTest() = default;
    virtual ~DataProviderTest() = default;
};
IMPLEMENT_SYMBOLIC(DataProviderTest);

/////////////////SymbolicFactory////////////////////////////

BOOST_AUTO_TEST_CASE(SymbolicFactory_getInstance_test)
{
    using namespace winglib;
    auto singleton = SymbolicFactory::getInstance();
    auto singleton2 = SymbolicFactory::getInstance();

    BOOST_ASSERT(singleton);
    BOOST_TEST(singleton);
    BOOST_TEST(singleton == singleton2);
}

BOOST_AUTO_TEST_CASE(SymbolicFactory_getSymbolicTest)
{
    using namespace winglib;
    const auto& symbolic_name = SymbolicTest::symbolName();
    SymbolicBase* symbolic = SymbolicFactory::getSymbolic(symbolic_name, nullptr);

    BOOST_ASSERT(symbolic);
    BOOST_TEST(symbolic_name == symbolic->name());
    
}

/////////////////SymbolicBase//////////////////////////////.
BOOST_AUTO_TEST_CASE(SymbolicBase_name)
{
    const auto&  dataProviderStaticName = DataProviderTest::symbolName();
    
    using namespace winglib;
    SymbolicBase *dp = SymbolicFactory::getSymbolic(dataProviderStaticName, nullptr);
    const auto&  dataProviderName = dp->name();
    
    delete dp;
    BOOST_CHECK(!dataProviderStaticName.empty());
    BOOST_CHECK(!dataProviderName.empty());
    BOOST_TEST(dataProviderStaticName == dataProviderName);
}

BOOST_AUTO_TEST_CASE(SymbolicBase_demangledName)
{
    const auto& name = typeid(DataProviderTest).name();
    const auto& boost_name = boost::core::demangle(name);

    const auto& symbolic_name = winglib::SymbolicBase::demangledName(name);

    //using namespace std;
    //cout << name << endl;
    //cout << boost_name << endl;
    //cout << symbolic_name << endl;

    BOOST_CHECK(!boost_name.empty());
    BOOST_CHECK(!symbolic_name.empty());
    BOOST_TEST(boost_name == symbolic_name);
}
