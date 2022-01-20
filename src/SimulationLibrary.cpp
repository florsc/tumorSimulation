//
// Created by florian on 9/10/21.
//

#include "SimulationSetUp/ParameterStruct.h"
#include "SimulationSetUp/TargetSetUp/SphericalTargetSetUpParameters.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>
#include <mutex>
#include "SimulationLibrary.h"
#include "util/HelperFunctions.h"
#include "util/Samplers.h"
#include "Managers/SimulationManager.h"

//runs simulation with different probabilities of branching several times, with same conditions for each probability each run
int run() {

    // simulation parameters
    int numberOfRuns = 10; //how many runs for each instance with different probability
    int numberOfTargets = 5;
    int summedVolumeOfAllTargets = 1000000;
    std::vector<double> branchingProbabilities({0, 0.005, 0.01, 0.05, 0.1, 0.2, 0.5}); //branching probabilities for different simulation instances, sets implicitly the number of instances



    std::string directory = "../created_data/simulation_data/";
    std::string fileName = directory + "simRes";

    auto generator = GeneratorSingleton::getInstance()->m_generator;
    HelperFunctions::deleteDirectoryContents(directory);
    for (int i = 0; i < branchingProbabilities.size(); i++) {
        std::ofstream myfile;
        myfile.open(fileName +"_" +std::to_string(branchingProbabilities[i]));
        myfile.close();
    }
    for (int i = 0; i < numberOfRuns; i++) {
        ParameterStruct parameters;
        parameters.createRandomTargets(numberOfTargets, numberOfTargets, summedVolumeOfAllTargets);

        //samples the starting angles, should be the same for each probability
        auto angleSampler = std::shared_ptr<FixedValuesSampler>(new FixedValuesSampler(
                {std::uniform_real_distribution<>(0.0, M_PI)(*generator),
                 std::uniform_real_distribution<>(0.0, 2 * M_PI)(*generator)}));

        //Here are RazettiParameters set, when using RandomDirection this must be changed
        auto razettiSetUpParameters = std::make_shared<RazettiSetUpParameters>();
        razettiSetUpParameters->startAngleSampler = angleSampler;
        parameters.axonSetUpParameters = razettiSetUpParameters;


        for (const auto &branchingProbability: branchingProbabilities) {
            parameters.axonSetUpParameters->branchingProbability = branchingProbability;
            angleSampler->reset();

            auto simulationManager = std::make_shared<SimulationManager>(parameters);
            simulationManager->setUp(parameters, simulationManager);
            simulationManager->run();
            auto targetReached = simulationManager->getNumberOfTargetReached();
            auto length = simulationManager->getAxonLength();
            auto branches = simulationManager->getNumberOfAxons() - 1;

            targetReached += targetReached;

            std::ofstream myfile;
            myfile.open(fileName + "_" + std::to_string(branchingProbability), std::ios_base::app);
            myfile << branchingProbability << " " << branches << " " << targetReached << " " << length << std::endl;
            myfile.close();
        }


    }
    std::cout << "simulation finished" << std::endl;
    return 0;

}

//runs simulation once to create data for visualization
int run_visualization() {

    auto generator = GeneratorSingleton::getInstance()->m_generator;
    std::string directory = "../created_data/visualization_data/";
    std::string axonFileName = directory + "cpp_results.json";
    std::string targetsFileName = directory + "targets.json";
    double branchingProbability = 0.01;

    HelperFunctions::deleteDirectoryContents(directory);


    ParameterStruct parameters;
    parameters.createRandomTargets(5, 5, 1000000);
    parameters.axonSetUpParameters->branchingProbability = branchingProbability;

    auto simulationManager = std::make_shared<SimulationManager>(parameters);
    simulationManager->setUp(parameters, simulationManager);
    simulationManager->run();

    std::vector<std::vector<std::vector<double>>> vec = simulationManager->getAxonPositions();
    nlohmann::json ja(vec);
    std::ofstream myfile;
    myfile.open(axonFileName);
    myfile << ja.dump();
    myfile.close();

    nlohmann::json jt(vec);
    for (const auto& target:parameters.targets) {
        auto sphericalTargetsSetUp = std::dynamic_pointer_cast<SphericalTargetSetUpParameters>(
                target);
        jt.emplace_back(sphericalTargetsSetUp->radius);
    }
    std::ofstream myfile2;
    myfile.open(targetsFileName);
    myfile << jt.dump();
    myfile.close();


    std::cout << "simulation finished" << std::endl;
    return 0;

}