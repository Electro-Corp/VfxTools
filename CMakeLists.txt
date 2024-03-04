cmake_minimum_required(VERSION 3.12)

project(vfxTools)

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PNG REQUIRED)

# Include directories
include_directories(src)
include_directories(/usr/local/include)
include_directories(${PNG_INCLUDE_DIR})


# Compiler executable
add_executable(vfxTools
    src/main.cpp
    src/vfxtools.cpp
    src/frame.cpp

    # Math
    src/math/conv.cpp

    # Tools
    src/tool.cpp
    src/tools/opticalflow.cpp
    src/tools/shittyvhs.cpp
)


# Flags
target_compile_options(vfxTools PUBLIC -fpermissive -g -O2 -I/usr/include/libpng16)
target_link_libraries(vfxTools PUBLIC ${PNG_LIBRARY})