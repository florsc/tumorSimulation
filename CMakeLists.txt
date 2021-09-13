cmake_minimum_required(VERSION 3.20)
PROJECT ( tumorSimulation C CXX )
project(tumorSimulation)
cmake_minimum_required (VERSION 2.6)
find_package (Threads)
add_executable (tumorSimulation main.cpp cmake-build-debug/Axon.cpp cmake-build-debug/Axon.h cmake-build-debug/OccupiedSpace.cpp cmake-build-debug/OccupiedSpace.h)
add_library(simulationLibrary SHARED cmake-build-debug/SimulationLibrary.cpp cmake-build-debug/SimulationLibrary.h cmake-build-debug/Axon.cpp cmake-build-debug/Axon.h)




include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tests
        Axon.h
        Axon.cpp
        cmake-build-debug/Testing/test.cpp)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
target_link_libraries (tumorSimulation ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (tumorSimulation PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(
        tests
        gtest_main
        simulationLibrary
)

include(GoogleTest)
gtest_discover_tests(tests)