#define BOOST_TEST_MODULE SymbolicFactoryTest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

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

BOOST_AUTO_TEST_CASE(SymbolicBase_invalid_demangleName)
{
    auto name = "invalid";
    std::function<bool(const std::exception &)> fp = [](const std::exception &e) {
        //cout << e.what() << endl; // expecting run_time error with : Mangled_name [" + std::string(inputName) + "] is not a valid for boost::core::demangler
        return e.what() == std::string("Mangled_name [invalid] is not a valid input for boost::core::demangler");
    };

    // Get the symbol from the factory
    BOOST_CHECK_EXCEPTION(winglib::SymbolicBase::demangledName(name), std::runtime_error, fp);
}
