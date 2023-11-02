## Naming the executable "boost_test_runner" in this project as :
## 1. it is already under the SymbolicFactory directory path
## 2. signals to the caller that this executable supports all the standard run time arguments
##    for boost_unit_test framework

#add_executable(boost_test_runner main/ref.cpp main/SymbolicFactoryTest.cpp pair_llm/SymbolicFactoryTest.cpp)
add_executable(boost_test_runner main/ref.cpp main/SymbolicFactoryTest.cpp pair_llm/llm_SymbolicFactory.cpp)

set(project_home ${PROJECT_BINARY_DIR})

# opt to use the long form than generator expressions to make the logic more descriptive
if (DEFINED ENV{BOOST_HOME})
    set(boost_home $ENV{BOOST_HOME})
else ()
    set(boost_home "/opt/homebrew")
endif ()

# TODO: for include - test folder should pickup the header from the source folder instead
# of the installed dir. The installed dir should be populated after the successful build/tests
target_include_directories(boost_test_runner PUBLIC ${boost_home}/include ${project_home}/include)
target_link_directories(boost_test_runner PUBLIC ${boost_home}/lib ${project_home}/lib)

target_link_libraries(boost_test_runner PUBLIC boost_unit_test_framework SymbolicFactory project_compiler_flags)


#add_subdirectory(main)
#add_subdirectory(pair_llm)