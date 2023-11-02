# if the header file changed, invoke LLM to regenerate the boost unit tests
# CMake commands are based on answers in : 
# https://stackoverflow.com/questions/49053544/how-do-i-run-a-python-script-every-time-in-a-cmake-build
#
#add_executable(pair_llm_test main.cpp gen_symbolicfactory.cpp)


## trigger always
add_custom_target(
        gen_symbolic_base_target ALL echo "custom target gen_symbolic_base_target trigger always"
        DEPENDS ${PROJECT_BINARY_DIR}/include/SymbolicBase.hpp
)

add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/__header.h
            ${CMAKE_CURRENT_BINARY_DIR}/header.h
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OriginalHeader.h
        COMMAND python ${py_cmd}
)
