cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project("Saper")

add_executable(saper main.cpp GameArea.cpp Field.cpp)
target_link_libraries(saper PRIVATE sfml-graphics sfml-system sfml-window)
