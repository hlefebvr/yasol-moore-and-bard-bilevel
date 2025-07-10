cmake_minimum_required(VERSION 3.31)
project(cpp)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

# idol
set(USE_CPLEX ON)
include(FetchContent)
FetchContent_Declare(
        idol
        GIT_REPOSITORY https://github.com/hlefebvr/idol.git
        GIT_TAG        origin/main
)
FetchContent_MakeAvailable(idol)

# yasol
find_package(Yasol REQUIRED)

add_executable(cpp main.cpp)
target_compile_definitions(cpp PUBLIC COMPILE_WITH_CPLEX_C NO_CGL)
target_link_libraries(cpp PUBLIC idol Yasol::Yasol)
