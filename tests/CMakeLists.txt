## Naming the executable "boost_test_runner" in this project as :
## 1. it is already under the SymbolicFactory directory path
## 2. signals to the caller that this executable supports all the standard run time arguments
##    for boost_unit_test framework

add_executable(boost_test_runner main/ref.cpp main/SymbolicFactoryTest.cpp pair_llm/llm_SymbolicFactory.cpp)

set(SymbolicFactory_include ${PROJECT_SOURCE_DIR}/SymbolicFactory)
set(SymbolicFactory_lib ${PROJECT_BINARY_DIR}/SymbolicFactory)

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED COMPONENTS system unit_test_framework)

message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
message(STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")


# the sample executable should pickup the header from the source folder instead
# of the installed dir. The installed dir would populate after the successful build/tests
target_include_directories(boost_test_runner PUBLIC ${Boost_INCLUDE_DIRS} ${SymbolicFactory_include})
target_link_directories(boost_test_runner PUBLIC ${Boost_LIBRARY_DIRS} ${SymbolicFactory_lib})
target_link_libraries(boost_test_runner PUBLIC ${Boost_LIBRARIES} SymbolicFactory project_compiler_flags)

