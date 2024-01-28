cmake_minimum_required(VERSION 3.27)
project(FrogDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Drogon CONFIG REQUIRED)

find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

include(FetchContent)

FetchContent_Declare(
        webxx
        GIT_REPOSITORY https://github.com/rthrfrd/webxx
        GIT_TAG 40b99f345ac8092ebabeb8a8faf0f8fc84ac3e3a
)
FetchContent_MakeAvailable(webxx)

add_executable(FrogDemo main.cpp
        src/htmx.h
        src/components/components.h
        src/components/components.cpp
        src/controllers/frog_ctl_Home.h
        src/controllers/frog_ctl_Home.cc
        src/controllers/frog_ctl_Treasuries.h
        src/controllers/frog_ctl_Treasuries.cc
        src/controllers/utils.h
        src/controllers/utils.cpp
)

target_include_directories(FrogDemo PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(FrogDemo
        PRIVATE
        Drogon::Drogon
        webxx
        Qt::Core
)

