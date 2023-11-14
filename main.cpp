#include "SymbolicFactory/SymbolicBase.hpp"
#include "SymbolicFactory/SymbolicFactory.hpp"
#include <iostream>
#include <exception>

using namespace winglib;

namespace wingTest
{
    // TODO: do we need a special macro to deal with cases where
    // a parent class/interface is needed in the class hierarchy ?
    // or how to handle multiple inheritance ?
    class ProviderBase : protected SymbolicBase
    {
    public:
        ProviderBase() = default;
        virtual ~ProviderBase() = default;

    protected:
        ProviderBase(const char *symbol) : SymbolicBase(symbol, (SymbolicBase *)nullptr){};
    };

    ////////////////////////////////////////////////////////////////////////////////
    // DECLARE Symbolic
    DECLARE_SYMBOLIC(DataProvider)
public:
    DataProvider() = default;
    virtual ~DataProvider() = default;
};
IMPLEMENT_SYMBOLIC(DataProvider)

/////////////////////////////////////////////////////////////////////////////////
DECLARE_SYMBOLIC(ExecutionProvider)
public:
ExecutionProvider() = default;
virtual ~ExecutionProvider() = default;
}
;
IMPLEMENT_SYMBOLIC(ExecutionProvider)
}
;

int main(int, char **)
{
    auto sf = SymbolicFactory::getInstance();

    //
    std::cout << typeid(wingTest::ExecutionProvider).name() << std::endl;
    // std::cout << ep.symbolName() << std::endl;

    try
    {
        // call factory using class static sybolName() method - allow compile time check
        auto sb = sf->getSymbolic(wingTest::DataProvider::symbolName(), nullptr);
        std::cout << "Hello World: " << sb->name() << std::endl;

        // call factory using a hand crafted string (i.e. read via config file)
        auto sb2 = sf->getSymbolic("wingTest::ExecutionProvider", nullptr);
        std::cout << "Hello World: " << sb2->name() << std::endl;
        // std::cout << wingTest::ExecutionProvider::symbolName() << std::endl;
        exit(0);
    }
    catch (exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}