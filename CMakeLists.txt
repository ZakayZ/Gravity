cmake_minimum_required(VERSION 3.21)
project(Gravity)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(CMAKE_CXX_STANDARD 17)

add_executable(Gravity main.cpp Solver/RungeKutta4.cpp Satellite/Position.cpp Satellite/Satellite.cpp Simulation.cpp StabilityTester.cpp)
target_link_directories(Gravity PUBLIC ./)
target_link_libraries(Gravity Eigen3::Eigen)