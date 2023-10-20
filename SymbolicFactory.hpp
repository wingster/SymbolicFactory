#pragma once

// Use std map to store class function pointer
#include <map>
#include "SymbolicBase.hpp"
using namespace std;

namespace winglib
{
    class SymbolicFactory
    {
    public:
        static SymbolicFactory *getInstance(); // singleton method
        static SymbolicBase *registerSymbol(const string &symbol, SymbolicBase *classPtr);
        static SymbolicBase *getSymbolic(const string &symbol, void *);

    private:
        SymbolicFactory() = default; // make default ctor private
        map<string, SymbolicBase *> factoryMap_;
    };
}
