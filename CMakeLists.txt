cmake_minimum_required(VERSION 3.14)
project(FTXUIHelloWorld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_library(app_lib app.cpp)
target_link_libraries(app_lib PUBLIC ftxui::screen ftxui::dom ftxui::component)

add_executable(hello_world main.cpp)
target_link_libraries(hello_world PRIVATE app_lib)

# Phase 1: Setup Catch2 Test Environment
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(run_tests test_main.cpp)
target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain app_lib)
