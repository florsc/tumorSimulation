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

int run() {
    //unsigned long const hardware_threads=1;//std::max(std::thread::hardware_concurrency(),2u);
    //std::cout<<"number of threads: "<<hardware_threads<<std::endl;
    //std::vector<std::thread> threads;
    //std::mutex simulationDataMutex;


    int numberOfRuns = 10;


    auto generator =GeneratorSingleton::getInstance()->m_generator;
    std::string fileName = "simRes";
    std::vector<double> branchingProbabilities({0,0.005,0.01,0.05,0.1,0.2,0.5});

    for(int i = 0;i<numberOfRuns;i++)
    {std::ofstream myfile;
        myfile.open(fileName);
        myfile.close();}
    for(int i = 0;i<numberOfRuns;i++) {
        ParameterStruct parameters;
        parameters.createRandomTargets(5,5,100000000);
        auto angleSampler = std::shared_ptr<FixedValuesSampler>(new FixedValuesSampler({std::uniform_real_distribution<>(0.0, M_PI)(*generator), std::uniform_real_distribution<>(0.0, 2*M_PI)(*generator)}));
        auto razettiSetUpParameters = std::make_shared<RazettiSetUpParameters>();
        razettiSetUpParameters->angleSampler = angleSampler;
        parameters.axonSetUpParameters=razettiSetUpParameters;
        for(const auto& branchingProbability : branchingProbabilities) {
            parameters.axonSetUpParameters->branchingProbability=branchingProbability;
            angleSampler->reset();

            auto simulationManager = std::make_shared<SimulationManager>(parameters);
            simulationManager->setUp(parameters, simulationManager );
            simulationManager->run();
            auto targetReached = simulationManager->getNumberOfTargetReached();
            auto length = simulationManager->getAxonLength();
            auto branches = simulationManager->getNumberOfAxons()-1;

            targetReached += targetReached;
            double targetAxonLength;
            double axonLength;
            if (targetReached > 0) {
                targetAxonLength += length;
            }
            axonLength += length;

            std::vector<std::vector<std::vector<double>>> vec = simulationManager->getAxonPositions();
            nlohmann::json j(vec);
            std::ofstream myfile;
            myfile.open("cpp_results.json");
            myfile << j.dump();
            myfile.close();

            std::ofstream myfile2;
            myfile2.open(fileName+"_"+std::to_string(branchingProbability), std::ios_base::app);
            myfile2 << branchingProbability << " " << branches << " " << targetReached << " " << length << std::endl;
            myfile2.close();
        }
        std::cout << "Create json" << std::endl;
        std::vector<std::vector<double>> vec;
        for(const auto& targetSetUp:parameters.targets){
            if(auto sphericalTargetsSetUp = std::dynamic_pointer_cast<SphericalTargetSetUpParameters>(targetSetUp)){
                EuclideanVector targetPosition = sphericalTargetsSetUp->centerPoint;
                vec.push_back({targetPosition.at(0),targetPosition.at(1),targetPosition.at(2)});}
        }
        nlohmann::json j1(vec);
        auto sphericalTargetsSetUp = std::dynamic_pointer_cast<SphericalTargetSetUpParameters>(parameters.targets.at(0));
        j1.emplace_back(sphericalTargetsSetUp->radius);

        std::ofstream myfile;
        myfile.open("targets.json");
        std::cout << "Write to file" << std::endl;
        myfile << j1.dump();
        myfile.close();


    }
    /*
    threads.emplace_back(simulationInstance);}
    for(auto& entry: threads){
        entry.join();}
    */
    std::cout<<"simulation finished"<<std::endl;
    return 0;

}
