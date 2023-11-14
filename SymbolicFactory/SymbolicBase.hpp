#pragma once
#include <string>

// Preprocessor macro to setup the basic structure to enable dynamic instance creation by "symbolic" class name
// TODO: Support for classes with multiple inheritance ??
// TODO: create at this time invokes default constructor only - need to pass in the input pointer
#define DECLARE_SYMBOLIC(symbol) \
    class symbol : protected winglib::SymbolicBase \
    { \
        public: \
            symbol(const char *symName, SymbolicBase *) : SymbolicBase(symName, (SymbolicBase *)nullptr){}; \
            static std::string symbolName() { \
                return winglib::SymbolicBase::demangledName(typeid(symbol).name()); \
            } \
            std::shared_ptr<SymbolicBase> create(void *) const {\
                SymbolicBase* instance = new symbol(); \
                return std::shared_ptr<SymbolicBase>(instance); \
            } \

// Preprocessor macro to instantiate the exemplar instance for the factory map 
#define IMPLEMENT_SYMBOLIC(symbol) \
static symbol symbol##_exemplar(winglib::SymbolicBase::demangledName(typeid(symbol).name()).c_str(), (winglib::SymbolicBase *)nullptr); 

/*
static auto* symbol##_exemplar = new symbol(winglib::SymbolicBase::demangledName(typeid(symbol).name()).c_str(), (winglib::SymbolicBase *)nullptr); \
static shared_ptr<winglib::SymbolicBase> symbol##_exemplar_shared((winglib::SymbolicBase*)symbol##_exemplar);
*/

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
        virtual std::shared_ptr<SymbolicBase> create(void*) const = 0;

        // utility function (thus static) to get demangled type name - compiler/platform specific
        // TODO: Consider moving this out from the base class to a general purpose utilities to hide platform/compiler specific implementations
        static std::string demangledName(const char *);
    protected:
        SymbolicBase() = default;
};

}