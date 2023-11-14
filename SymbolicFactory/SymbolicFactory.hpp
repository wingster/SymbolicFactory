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
        // Get singleton factory instance
        static shared_ptr<SymbolicFactory> getInstance(); 
        static shared_ptr<SymbolicBase> getSymbolic(const string &symbol, void *);

    private:
        SymbolicFactory() = default; // make default ctor private
        map<string, SymbolicBase*> factoryMap_;
        
        // Add symbols to the factory map -> only allowed from Symbolic ctors
        static void registerSymbol(const string &symbol, SymbolicBase* exemplar);
        friend class SymbolicBase;
    };
}
