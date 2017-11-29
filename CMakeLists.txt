cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/DespiteDeath/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "f87f234951173424a4436d866252feeb849a9500"
)

project(demo)

hunter_add_package(print)
hunter_add_package(Boost COMPONENTS filesystem  system program_options)

find_package(print)
find_package(Boost COMPONENTS filesystem system program_options REQUIRED)

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)

target_link_libraries(demo print Boost::filesystem Boost::system  Boost::program_options)

install(TARGETS demo RUNTIME DESTINATION bin)
