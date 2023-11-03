#include "SymbolicBase.hpp"
#include "SymbolicFactory.hpp"
#include <typeinfo>
#include <string>
#include <exception>
#include <stdexcept>
#include <cxxabi.h>   // TODO: This header may be platform dependent, consider switching to boost class demanagler

namespace winglib
{
    SymbolicBase::SymbolicBase(const char *symbolicName, SymbolicBase *)
    {
        // note that symbolic base is unused, the this pointer is used here.
        // the SymbolicBase* is added to signature to avoid any collison with any user-defined constructors
        SymbolicFactory::registerSymbol(std::string(symbolicName), this);
    }

    // Using cxxabi to demangle class name. Consider switching to a more generic function
    std::string SymbolicBase::demangledName(const char *inputName)
    {
        size_t demangledLength = 0;
        int status = 0;
        char *resultPtr = abi::__cxa_demangle(inputName, NULL, &demangledLength, &status);
        std::string ret;
        std::string exMsg;
        switch (status)
        {
        case 0:
            ret = resultPtr;
            delete (resultPtr);

            return ret;
        case -1:
            exMsg = "A memory allocation failure occured";
            break;
        case -2:
            exMsg = "Mangled_name [" + std::string(inputName) + "] is not a valid name under the C++ ABI mangling rules";
            break;
        case -3:
            exMsg = "One of the arugments is invalid";
            break;
        default:
            exMsg = "Unexpected exception in demangledName";
        }
        // Exception - throw RunTime error w/ exception message
        auto re = runtime_error(exMsg);
        throw(re);
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