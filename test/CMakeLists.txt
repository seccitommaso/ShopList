cmake_minimum_required(VERSION 3.27)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
set(gmock_SOURCE_DIR, ./lib/googletest/)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
set(TEST_SOURCE_FILES runAllTests.cpp ItemTest.cpp ShoppingListTest.cpp UserTest.cpp)
add_executable(runShopListTests ${TEST_SOURCE_FILES})
target_link_libraries(runShopListTests gtest gtest_main gmock gmock_main core)
