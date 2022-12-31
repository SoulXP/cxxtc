# Test configuration
find_package(Catch2 REQUIRED)
find_path(CATCH2_CMAKE NAMES Catch2Config.cmake PATH_SUFFIX Catch2)

# Handle compiler test definitions
if (ENABLE_STATIC_TESTS STREQUAL "on" OR ENABLE_STATIC_TESTS STREQUAL "true" OR ENABLE_STATIC_TESTS STREQUAL "1")
    message(STATUS "Enabling static tests for this build")
    add_compile_definitions(ENABLE_STATIC_TESTS)
endif()

# Library tests
add_executable(timecode_basic.test timecode_basic.test.cpp)
add_executable(timecode_fps.test timecode_fps.test.cpp)
target_link_libraries(timecode_basic.test PRIVATE Catch2::Catch2WithMain magic_enum::magic_enum)
target_link_libraries(timecode_fps.test PRIVATE Catch2::Catch2WithMain magic_enum::magic_enum)

include(CTest)
include(Catch)
catch_discover_tests(timecode_basic.test)
catch_discover_tests(timecode_fps.test)
