cmake_minimum_required(VERSION 3.14)
project(pcclist_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(pcclist INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
)
add_library(pcclist_test INTERFACE)
target_compile_features(pcclist_test INTERFACE cxx_std_17)

add_executable(test_pcclist
    test_pcclist.cc
)

target_link_libraries(test_pcclist
    PRIVATE
      GTest::gtest_main
      GTest::gmock       
      pcclist
)

add_test(NAME pcclist_test COMMAND test_pcclist)

# add_executable(fuzz_pcclist
#     fuzz_pcclist.cc
# )

# target_link_libraries(fuzz_pcclist
#     PRIVATE
#     pcclist
#     fuzzer           # the libFuzzer library built above
# )

# target_link_options(fuzz_pcclist PRIVATE
#     -fsanitize=address,fuzzer
# )