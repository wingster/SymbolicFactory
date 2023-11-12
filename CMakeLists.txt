cmake_minimum_required(VERSION 3.15)

# project name and version
project(wl VERSION 0.0)

# specify the C++ standard
add_library(project_compiler_flags INTERFACE)
target_compile_features(project_compiler_flags INTERFACE cxx_std_20)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(project_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# build sub-modules
add_subdirectory(SymbolicFactory)
add_subdirectory(tests)

message("project binary dir : " ${PROJECT_BINARY_DIR})

# Simple Test executable depends on SymbolicFactory library
add_executable(SymbolicTest main.cpp)
target_link_libraries(SymbolicTest PUBLIC SymbolicFactory project_compiler_flags)


##
## TESTS
## create and configure the unit test target
##
## Not using CTest/CDash for now
##include(CTest)
enable_testing()
add_test(NAME boost_test 
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests 
         COMMAND boost_test_runner   
        )
add_test(NAME main_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
         COMMAND SymbolicTest
        )




