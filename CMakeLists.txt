cmake_minimum_required(VERSION 3.20)
PROJECT ( tumorSimulation C CXX )
project(tumorSimulation)
set(CMAKE_CXX_FLAGS "-std=c++17")
cmake_minimum_required (VERSION 2.6)
find_package (Threads)
add_library(simulationLibrary SHARED src/SimulationLibrary.cpp src/SimulationLibrary.h src/ConstraintHandler.h src/ConstraintHandler.cpp src/Axon.cpp src/Axon.h src/helperFunctions.cpp src/helperFunctions.h src/ExteriorLimit.cpp src/ExteriorLimit.h src/EuclideanVector.cpp src/EuclideanVector.h src/AxonManager.cpp src/AxonManager.h src/ProcessSampler.cpp src/ProcessSampler.h)




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
        src/Axon.h
        src/Axon.cpp
        src/Tests/helperFunctionTest.cpp
        src/helperFunctions.cpp src/helperFunctions.h src/Tests/axonTest.cpp src/Tests/generalTest.cpp src/EuclideanVector.cpp src/EuclideanVector.h src/Tests/constraintHandlerTest.cpp src/Tests/axonManagerTest.cpp)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
target_link_libraries (simulationLibrary ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (simulationLibrary  nlohmann_json::nlohmann_json)
target_link_libraries(
        tests
        gtest_main
        simulationLibrary
)

include(GoogleTest)
gtest_discover_tests(tests)