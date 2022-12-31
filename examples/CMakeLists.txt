# Examples configuration

# Library examples
add_executable(timecode_basic-initialization.example timecode_basic-initialization.example.cpp)
target_link_libraries(timecode_basic-initialization.example PRIVATE magic_enum::magic_enum)
