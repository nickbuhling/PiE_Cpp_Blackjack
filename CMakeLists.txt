cmake_minimum_required(VERSION 3.26)
project(PiE_Cpp_Blackjack)

set(CMAKE_CXX_STANDARD 17)

add_executable(PiE_Cpp_Blackjack main.cpp
        Card.cpp
        Hand.cpp
        Blackjack.cpp
        Blackjack.h)
