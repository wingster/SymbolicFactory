add_executable(base_test ref.cpp)

target_include_directories(base_test PUBLIC "/opt/homebrew/include")
target_link_directories(base_test PUBLIC "/opt/homebrew/lib")

target_link_libraries(base_test PUBLIC boost_unit_test_framework project_compiler_flags)
