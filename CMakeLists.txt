cmake_minimum_required(VERSION 3.5)

project(MySTL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES main.cpp
    myvector.h
    myExceptions.h
    myIterator.h)
add_executable(MySTL ${SOURCES})

include(GNUInstallDirs)
install(TARGETS MySTL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
