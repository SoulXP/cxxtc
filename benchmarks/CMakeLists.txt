# Test configuration
find_package(Catch2 REQUIRED)
find_path(CATCH2_CMAKE NAMES Catch2Config.cmake PATH_SUFFIX Catch2)

# Benchmark tests
add_executable(timecode_basic.bench.cpp timecode_basic.bench.cpp)
target_link_libraries(timecode_basic.bench.cpp PRIVATE Catch2::Catch2WithMain magic_enum::magic_enum)

include(CTest)
include(Catch)
catch_discover_tests(timecode_basic.bench.cpp)
