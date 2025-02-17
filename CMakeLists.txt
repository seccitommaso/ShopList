cmake_minimum_required(VERSION 3.27)
project(ShopList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ShopList main.cpp
        User.cpp
        User.h
        Subject.h
        Observer.h
        ShoppingList.cpp
        ShoppingList.h
        Item.cpp
        Item.h
        nnn.cpp
        nnn.h)
