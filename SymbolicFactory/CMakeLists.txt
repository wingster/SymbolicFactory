add_library(SymbolicFactory SHARED SymbolicBase.cpp SymbolicFactory.cpp)

# Add required Boost components for this sub-module
# boost.core (demangle.hpp)
# reference for windows build : https://stackoverflow.com/questions/28887680/linking-boost-library-with-boost-use-static-lib-off-on-windows

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED COMPONENTS system)

message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
message(STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")

target_include_directories(SymbolicFactory PUBLIC ${Boost_INCLUDE_DIRS} )
target_link_libraries(SymbolicFactory PUBLIC ${Boost_LIBRARIES} project_compiler_flags)

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