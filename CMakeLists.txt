cmake_minimum_required(VERSION 3.20)
PROJECT(tumorSimulation C CXX)
project(tumorSimulation)
set(CMAKE_CXX_FLAGS "-std=c++17")
cmake_minimum_required(VERSION 2.6)
find_package(Threads)
add_library(simulationLibrary SHARED
        src/SimulationLibrary.cpp
        src/SimulationLibrary.h
        src/Managers/ConstraintManager.h
        src/Managers/ConstraintManager.cpp
        src/util/HelperFunctions.cpp
        src/util/HelperFunctions.h
        src/ExteriorLimits/ExteriorLimit.cpp
        src/ExteriorLimits/ExteriorLimit.h
        src/util/EuclideanVector.cpp
        src/util/EuclideanVector.h
        src/Managers/SimulationManager.cpp
        src/Managers/SimulationManager.h
        src/SimulationSetUp/ParameterStruct.h
        src/SimulationSetUp/ParameterStruct.cpp
        src/Managers/AxonManagers/AxonManager.cpp
        src/Managers/AxonManagers/AxonManager.h
        src/Axons/AxonTypes/BaseAxon/BaseAxon.cpp
        src/Axons/AxonTypes/BaseAxon/BaseAxon.h
        src/Axons/AxonTypes/RazettiAxon/RazettiAxon.cpp
        src/Axons/AxonTypes/RazettiAxon/RazettiAxon.h
        src/util/TypeDefs.h src/Axons/Factories/AxonFactory.cpp
        src/Axons/Factories/AxonFactory.h
        src/Axons/Factories/RazettiFactory.cpp
        src/Axons/Factories/RazettiFactory.h
        src/SimulationSetUp/GrowthModels/RazettiSetUpParameters.h
        src/SimulationSetUp/GrowthModels/AxonSetUpParameters.h
        src/Managers/AxonManagers/AxonManagerWaitingTime.cpp
        src/Managers/AxonManagers/AxonManagerWaitingTime.h
        src/Managers/AxonManagers/AxonManagerLinear.cpp
        src/Managers/AxonManagers/AxonManagerLinear.h
        src/SimulationSetUp/AxonOrder/AxonOrderData.h
        src/SimulationSetUp/AxonOrder/AxonOrderSampledWaitingTimeData.cpp
        src/SimulationSetUp/AxonOrder/AxonOrderSampledWaitingTimeData.h
        src/SimulationSetUp/AxonOrder/AxonOrderLinearData.cpp
        src/SimulationSetUp/AxonOrder/AxonOrderLinearData.h
        src/util/Samplers.h
        src/Axons/AxonTypes/RandomDirectionAxon/RandomDirectionAxon.cpp
        src/Axons/AxonTypes/RandomDirectionAxon/RandomDirectionAxon.h
        src/Axons/Factories/RandomDirectionFactory.cpp
        src/Axons/Factories/RandomDirectionFactory.h
        src/SimulationSetUp/GrowthModels/RandomDirectionSetUpParameters.h
        src/Managers/TargetManager.cpp src/Managers/TargetManager.h
        src/Targets/Target.h src/Targets/SphericalTarget.cpp
        src/Targets/SphericalTarget.h
        src/Axons/AxonTypes/BaseAxon/BaseAxonParameters.h
        src/Axons/AxonTypes/RazettiAxon/RazettiAxonParameters.h
        src/Axons/AxonTypes/RandomDirectionAxon/RandomDirectionAxonParameters.h
        src/SimulationSetUp/GrowthModels/RandomDirectionSetUpParameters.cpp
        src/SimulationSetUp/GrowthModels/RazettiSetUpParameters.h
        src/SimulationSetUp/GrowthModels/RazettiSetUpParameters.cpp
        src/util/SimulationException.h src/util/GeneratorSingleton.h src/util/GeneratorSingleton.cpp src/SimulationSetUp/GrowthModels/AxonSetUpParameters.cpp src/SimulationSetUp/ConstraintSetUp/ExteriorLimitSetUpParameters.cpp src/SimulationSetUp/ConstraintSetUp/ExteriorLimitSetUpParameters.h src/SimulationSetUp/ConstraintSetUp/SphericalLimitSetUpParameters.cpp src/SimulationSetUp/ConstraintSetUp/SphericalLimitSetUpParameters.h src/SimulationSetUp/TargetSetUp/TargetSetUpParameters.h src/SimulationSetUp/TargetSetUp/SphericalTargetSetUpParameters.cpp src/SimulationSetUp/TargetSetUp/SphericalTargetSetUpParameters.h src/util/DynamicCreators.cpp src/util/DynamicCreators.h)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")


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
        src/Tests/helperFunctionTest.cpp
        src/util/HelperFunctions.cpp src/util/HelperFunctions.h src/Tests/axonTest.cpp src/Tests/generalTest.cpp src/util/EuclideanVector.cpp src/util/EuclideanVector.h src/Tests/constraintHandlerTest.cpp src/Tests/simulationManagerTest.cpp src/Tests/axonManagerTest.cpp        src/SimulationSetUp/GrowthModels/RazettiSetUpParameters.h
        src/SimulationSetUp/GrowthModels/RazettiSetUpParameters.h
        src/SimulationSetUp/GrowthModels/RazettiSetUpParameters.cpp src/util/GeneratorSingleton.h src/Tests/visualizationTest.cpp)

add_executable(
        simulationRun
        src/util/HelperFunctions.cpp src/util/HelperFunctions.h src/Tests/generalTest.cpp src/util/EuclideanVector.cpp src/util/EuclideanVector.h)
add_executable(
        visualizationRun
        src/util/HelperFunctions.cpp src/util/HelperFunctions.h src/Tests/visualizationTest.cpp src/util/EuclideanVector.cpp src/util/EuclideanVector.h)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
target_link_libraries(simulationLibrary ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(simulationLibrary nlohmann_json::nlohmann_json)
target_link_libraries(
        tests
        gtest_main
        gmock_main
        simulationLibrary
        stdc++fs
)
target_link_libraries(
        simulationRun
        gtest_main
        gmock_main
        simulationLibrary
        stdc++fs
)
target_link_libraries(
        visualizationRun
        gtest_main
        gmock_main
        simulationLibrary
        stdc++fs
)

include(GoogleTest)
gtest_discover_tests(tests)
gtest_discover_tests(simulationRun)
gtest_discover_tests(visualizationRun)
