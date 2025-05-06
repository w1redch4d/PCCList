cmake_minimum_required(VERSION 3.8)
project(PCCList LANGUAGES CXX)

add_library(pcclist
    src/pcclist.cc
)

target_include_directories(pcclist
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(pcclist INTERFACE cxx_std_17)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)

add_executable(example example/main.cc)

target_link_libraries(example PRIVATE pcclist)