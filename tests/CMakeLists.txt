

add_executable(unit_tests main/ref.cpp main/SymbolicFactoryTest.cpp)


target_include_directories(unit_tests PUBLIC "/opt/homebrew/include")
target_link_directories(unit_tests PUBLIC "/opt/homebrew/lib")

target_link_libraries(unit_tests PUBLIC boost_unit_test_framework project_compiler_flags)



#add_subdirectory(main)
#add_subdirectory(pair_llm)