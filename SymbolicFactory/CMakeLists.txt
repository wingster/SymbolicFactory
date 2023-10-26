add_library(SymbolicFactory SHARED SymbolicBase.cpp SymbolicFactory.cpp)

target_link_libraries(SymbolicFactory PUBLIC project_compiler_flags)


# setup the version numbering
set_property(TARGET SymbolicFactory PROPERTY VERSION "0.0.0")
set_property(TARGET SymbolicFactory PROPERTY SOVERSION "0")
