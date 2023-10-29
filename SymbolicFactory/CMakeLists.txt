add_library(SymbolicFactory SHARED SymbolicBase.cpp SymbolicFactory.cpp)

target_link_libraries(SymbolicFactory PUBLIC project_compiler_flags)

# setup the version numbering - part of the shared object file suffix
set_property(TARGET SymbolicFactory PROPERTY VERSION "0.0.0")
set_property(TARGET SymbolicFactory PROPERTY SOVERSION "0")

# installing artifacts : headers files/libraries
# install to PROJECT_BINARY_DIR for now
set(installable_libs SymbolicFactory project_compiler_flags)

# install library
install(TARGETS SymbolicFactory ${installable_libs} DESTINATION ${PROJECT_BINARY_DIR}/lib)
# install include headers
install(FILES SymbolicBase.hpp SymbolicFactory.hpp DESTINATION ${PROJECT_BINARY_DIR}/include)