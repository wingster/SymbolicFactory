# SymbolicFactory
C++ Factory to create object instance dynamically, using type name via class inheritance
C++ doesn't provide natively support. To acheive this behavior this solution use C preprocessor macros

Similar discussions/approaches on the web:
http://www.cs.sjsu.edu/~pearce/modules/lectures/oop/types/reflection/prototype.htm
https://stackoverflow.com/questions/1310214/register-an-object-creator-in-object-factory


Doc Generated via google.generativeai
prompt_template = """
Please write technical documentation for this code and \n
make it easy for a non C++ developer to understand:

{question}

Output the results in markdown
"""

## SymbolicBase Class

The `SymbolicBase` class is a base class for creating symbolic objects. Symbolic objects are objects that can be created without knowing their concrete type at compile time. This is useful for creating objects that are dynamically loaded at runtime, or for creating objects that are represented by a string or other identifier.

### Constructors

The `SymbolicBase` class has two constructors:

* `SymbolicBase(const char *symbolicName, SymbolicBase* exemplar)`: This constructor takes a symbolic name and an exemplar object. The symbolic name is used to identify the type of the object, and the exemplar object is used to provide a default set of values for the object's fields.
* `SymbolicBase()`: This constructor is the default constructor. It creates a symbolic object with no symbolic name or exemplar object.

### Methods

The `SymbolicBase` class has three methods:

* `name()`: This method returns the symbolic name of the object.
* `create()`: This method creates a new instance of the object.
* `demangledName()`: This method returns the demangled name of the object's type.

### Example

The following example shows how to create a symbolic object:

```c++
#include <iostream>
#include <winglib/symbolic.h>

int main()
{
    // Create a symbolic object for a `std::string`.
    winglib::Symbolic<std::string> string("std::string", nullptr);

    // Print the symbolic name of the object.
    std::cout << string.name() << std::endl;

    // Create a new instance of the object.
    std::string* str = string.create();

    // Print the value of the object.
    std::cout << *str << std::endl;

    return 0;
}
```

Output:

```
std::string
Hello world!
```

## DECLARE_SYMBOLIC and IMPLEMENT_SYMBOLIC Macros

The `DECLARE_SYMBOLIC` and `IMPLEMENT_SYMBOLIC` macros are used to create symbolic objects for a given type. The `DECLARE_SYMBOLIC` macro defines a class for the symbolic object, and the `IMPLEMENT_SYMBOLIC` macro creates an instance of the symbolic object.

The following example shows how to use the `DECLARE_SYMBOLIC` and `IMPLEMENT_SYMBOLIC` macros to create a symbolic object for a `std::string` type:

```c++
#include <winglib/symbolic.h>

DECLARE_SYMBOLIC(std::string);

IMPLEMENT_SYMBOLIC(std::string);
```

This code will create a symbolic object for the `std::string` type named `std::string_exemplar`. The `std::string_exemplar` object can be used to create new instances of `std::string` objects at runtime.

## Conclusion

The `SymbolicBase` class and the `DECLARE_SYMBOLIC` and `IMPLEMENT_SYMBOLIC` macros provide a way to create symbolic objects at runtime. This can be useful for creating objects that are dynamically loaded at runtime, or for creating objects that are represented by a string or other identifier.
