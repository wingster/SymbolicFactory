#pragma once
#include <string>

#define DECLARE_SYMBOLIC(symbol) \
    class symbol : protected winglib::SymbolicBase \
    { \
        public: \
            symbol(const char *symbol, SymbolicBase *) : SymbolicBase(symbol, (SymbolicBase *)nullptr){}; \
            static std::string symbolName() { \
                return winglib::SymbolicBase::demangledName(typeid(symbol).name()); \
            } \
            SymbolicBase *create(void *) const {\
                return new symbol(); \
            } \

#define IMPLEMENT_SYMBOLIC(symbol) \
static symbol symbol##_exemplar(SymbolicBase::demangledName(typeid(symbol).name()).c_str(), (SymbolicBase *)nullptr); 



namespace winglib{

class SymbolicBase
{
    public:
        // TODO: decide if std::string more appropriate for symbolic name (vs const char *)
        SymbolicBase(const char *symbolicName, SymbolicBase* exemplar);
        virtual ~SymbolicBase() = default;

        // name() : returns the polymorphic demanagled type name, i.e. required object handle
        virtual std::string name() const;  

        // create() : returns a new instance, used by symbolic factory
        // takes a void* pointer for now, but should update to a input dictionary for general purpose construction
        virtual SymbolicBase* create(void*) const = 0;

        // Utility function (thus static) to get demangled type name - compiler/platform specific
        // Consider moving this out from this class to a general purpose utilities to hide platform/compiler specific implementations
        static std::string demangledName(const char *);
    protected:
        SymbolicBase() = default;
};

}