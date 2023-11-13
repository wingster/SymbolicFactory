#include "SymbolicBase.hpp"
#include "SymbolicFactory.hpp"
#include <typeinfo>
#include <string>
#include <exception>
#include <stdexcept>
#include <boost/core/demangle.hpp>

namespace winglib
{
    SymbolicBase::SymbolicBase(const char *symbolicName, SymbolicBase *)
    {
        // note that symbolic base is unused, the this pointer is used here.
        // the SymbolicBase* is added to signature to avoid any collison with any user-defined constructors
        SymbolicFactory::registerSymbol(std::string(symbolicName), this);
    }

    // Using boost to demangle class name. Wrapped in this function as it was hidding platform specifc abi::cxa_demangle
    std::string SymbolicBase::demangledName(const char *inputName)
    {
        boost::core::scoped_demangled_name demangled(inputName);
        std::string ret, exMsg;
        const char *resultPtr = demangled.get();
        if (!resultPtr)
        {
            exMsg = "Mangled_name [" + std::string(inputName) + "] is not a valid for boost::core::demangler";
            auto re = runtime_error(exMsg);
            throw(re);
        }
        ret = resultPtr;
        return ret;
    }

    std::string SymbolicBase::name() const
    {
        // std::string typeName = typeid(*this).name();
        // std::string demangledName = abi::__cxa_demangle(typeName, )
        return demangledName(typeid(*this).name());
    }

    SymbolicBase *SymbolicBase::create(void *) const
    {
        string msg = "SymbolicBase::create() pure virtual invoked";

        auto re = runtime_error(msg);
        throw(re);
    }
}