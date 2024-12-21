cmake_minimum_required(VERSION 3.21)

project(circuits)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(circuits src/camera.cpp
                        src/main.cpp
                        src/object.cpp
                        src/renderer.cpp)

target_link_directories(circuits PRIVATE deps/SDL2/lib/x64
                                         deps/SDL2_ttf/lib/x64)

target_include_directories(circuits PRIVATE deps/SDL2/include
                                            deps/SDL2_ttf/include)

target_link_libraries(circuits sdl2 sdl2main sdl2_ttf)
