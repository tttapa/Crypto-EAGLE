# Add an executable with tests, and specify the source files to compile
add_executable(greet.test test-Greet.cpp)
# Link the test executable with the Google Test main entry point and the library
# under test
target_link_libraries(greet.test gtest_main greet)

# Add the tests to Google Test
include(GoogleTest)
if (NOT CMAKE_CROSSCOMPILING)
gtest_discover_tests(greet.test)
endif()