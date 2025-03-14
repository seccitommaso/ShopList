cmake_minimum_required(VERSION 3.27)
project(ShopList)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

set(SOURCE_FILES
        Observer.h
        Subject.h
        Item.h
        Item.cpp
        ShoppingList.h
        ShoppingList.cpp
        User.h
        User.cpp)
add_executable(ShopList main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(ShopList core)