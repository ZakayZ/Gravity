cmake_minimum_required(VERSION 3.21)
project(Gravity)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Boost 1.40.0 REQUIRED COMPONENTS system)

set(CMAKE_CXX_STANDARD 20)

add_executable(Gravity main.cpp Satellite/Position.cpp
        Satellite/Satellite.cpp
        Simulation/Simulation.cpp
        StabilityTester.cpp
        Simulation/PerturbationInitializer.cpp
        OrbitalPhysics.cpp
        Random/Randomizer.cpp
        Metrics/StabilityMetric.cpp
        GeneralQuaternion.cpp)

target_include_directories(Gravity PUBLIC .)

target_link_libraries(Gravity Eigen3::Eigen)
target_link_libraries(Gravity ${Boost_LIBRARIES})