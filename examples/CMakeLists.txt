# Examples configuration

set(examples_common)

# Library examples
add_executable(timecode_basic-increment.example timecode_basic-increment.example.cpp ${examples_common})
target_include_directories(timecode_basic-increment.example PRIVATE include)
target_link_libraries(timecode_basic-increment.example PRIVATE magic_enum::magic_enum)
