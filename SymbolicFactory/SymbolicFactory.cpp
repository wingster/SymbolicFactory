#include "SymbolicFactory.hpp"
#include <string>
#include <algorithm>
#include <exception>
#include <iostream>

namespace winglib{

shared_ptr<SymbolicFactory> SymbolicFactory::getInstance()
{
    static shared_ptr<SymbolicFactory> instance(new SymbolicFactory()); // for clang it cannot take make_shared<SymbolicFactory>() given ctor is private
    return instance;
}

void SymbolicFactory::registerSymbol(const string& symbol, SymbolicBase* classPtr)
{
    std::cout << "SymbolicFactory::registerSymbol(" << symbol << "," << classPtr << ")" << std::endl;
    auto sf = getInstance();
    auto &map = sf->factoryMap_;
    // check if symbol alrady exists or registered
    const auto& mapiter = map.find(symbol);
    if(mapiter != map.end()){
        //auto *exemplar = mapiter->second;  //TODO: Use exemplar address in error message
        string msg = "Symbol name : " + symbol + " already registered"; 
        auto re = runtime_error(msg);
        throw(re);
    }
    else{
        map[symbol] = classPtr;
    }
    return;
}

shared_ptr<SymbolicBase> SymbolicFactory::getSymbolic(const string& symbol, void *arg)
{
    // find the symbol in the factory map
    auto sf = getInstance();
    const auto& map = sf->factoryMap_;
    const auto& mapiter = map.find(symbol);
    shared_ptr<SymbolicBase> ret = nullptr;
    if(mapiter != map.end()){
        auto exemplar = mapiter->second;  
        ret = exemplar->create(arg); 
    }
    else{
        string msg = "Unexpected symbol name : " + symbol; 
        auto re = runtime_error(msg);
        throw(re);
    }
    return ret;

}

}