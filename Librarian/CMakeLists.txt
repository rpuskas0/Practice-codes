cmake_minimum_required(VERSION 2.6)
project(librarian)

add_executable(librarian main.cpp
                Ch9-Chrono.cpp
                Ch9-Librarian-Books.cpp
                Ch9-Librarian-Library.cpp)

install(TARGETS librarian RUNTIME DESTINATION bin)
