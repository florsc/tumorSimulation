//
// Created by florian on 9/10/21.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include "SimulationLibrary.h"
#include "util/HelperFunctions.h"
#include "Managers/SimulationManager.h"
class SimulationInstance {
    double m_branchingProbability;
    int& m_targetReached;
    double& m_axonLength;
    double& m_targetAxonLength;
    int m_runs;
    std::mutex& m_simulationDataMutex;
    std::string m_fileName;
public:
    SimulationInstance(double branchingProbability, int &targetReached, double &axonLength, double &targetAxonLength, int runs, std::mutex& simulationDataMutex, std::string fileName):m_branchingProbability(branchingProbability),m_targetReached(targetReached), m_axonLength(axonLength),m_targetAxonLength(targetAxonLength), m_simulationDataMutex(simulationDataMutex), m_runs(runs), m_fileName(fileName){
        std::ofstream myfile;
        myfile.open(m_fileName);
        myfile.close();}
    void operator()() {
        //for(int i = 0;i<m_runs;i++) {
          //  std::cout<<"run "<<i<<std::endl;
            //std::cout << "Initialize global parameters" << std::endl;
            parameters.init();
            //std::cout << "Create Simulation Manager" << std::endl;
            auto simulationManager = std::make_shared<SimulationManager>();
            //std::cout << "Set up simulation" << std::endl;
            simulationManager->setUp(simulationManager, m_branchingProbability);
            //std::cout << "Run Axon growth" << std::endl;
            simulationManager->run();
            auto targetReached = simulationManager->getNumberOfTargetReached();
            auto length = simulationManager->getAxonLength();
            auto branches = simulationManager->getNumberOfAxons()-1;
            std::lock_guard<std::mutex> guard(m_simulationDataMutex);

            m_targetReached += targetReached;
            if (targetReached > 0) {
                m_targetAxonLength += length;
            }
            m_axonLength += length;

            std::vector<std::vector<std::vector<double>>> vec = simulationManager->getAxonPositions();
            //std::cout << "Create json" << std::endl;
            nlohmann::json j(vec);
            std::ofstream myfile;
            myfile.open("cpp_results.json");
            //std::cout << "Write to file" << std::endl;
            myfile << j.dump();
            myfile.close();

            std::ofstream myfile2;
            myfile2.open(m_fileName, std::ios_base::app);
            myfile2 << m_branchingProbability << " " << branches << " " << targetReached << " " << length << std::endl;
            myfile2.close();

    }
};
int run() {
    int targetReached;
    double averageAxonLength;
    double averageTargetAxonLength;
    targetReached = 0;
    averageAxonLength = 0;
    averageTargetAxonLength = 0;

    unsigned long const hardware_threads=1;//std::max(std::thread::hardware_concurrency(),2u);
    std::cout<<"number of threads: "<<hardware_threads<<std::endl;
    std::vector<std::thread> threads;
    std::mutex simulationDataMutex;
    int numberOfRuns = 100;



    //for(int i = 0;i<hardware_threads-1;i++){
    SimulationInstance simulationInstance(0,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes0");
    SimulationInstance simulationInstanceBranching1(0.005,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes1" );
    SimulationInstance simulationInstanceBranching2(0.01,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes2" );
    SimulationInstance simulationInstanceBranching3(0.05,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes3" );
    SimulationInstance simulationInstanceBranching4(0.1,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes4" );
    SimulationInstance simulationInstanceBranching5(0.2,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes5" );
    SimulationInstance simulationInstanceBranching6(0.5,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes6" );
    //SimulationInstance simulationInstanceBranching7(0.5,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes7" );
    //SimulationInstance simulationInstanceBranching8(0.01,targetReached, averageAxonLength, averageTargetAxonLength, numberOfRuns/hardware_threads, simulationDataMutex,"simRes8" );


    for(int i = 0;i<numberOfRuns;i++) {
        std::cout<<i<<std::endl;
        parameters.createStartAngles();
        parameters.createRandomTargets(50,50,1000000);

        std::cout << "Create json" << std::endl;
        std::vector<std::vector<double>> vec;
        for(const auto& targetPosition:parameters.targetPositions){
            vec.push_back({targetPosition.at(0),targetPosition.at(1),targetPosition.at(2)});
        }
        nlohmann::json j1(vec);

        j1.emplace_back(parameters.radius);

        std::ofstream myfile;
        myfile.open("targets.json");
        std::cout << "Write to file" << std::endl;
        myfile << j1.dump();
        myfile.close();

        simulationInstance();
        simulationInstanceBranching1();
        simulationInstanceBranching2();
        simulationInstanceBranching3();
        simulationInstanceBranching4();
        simulationInstanceBranching5();
        simulationInstanceBranching6();
        //simulationInstanceBranching7();
        //simulationInstanceBranching8();


    }
    /*
    threads.emplace_back(simulationInstance);}
    for(auto& entry: threads){
        entry.join();}
*/
    std::cout<<targetReached<<std::endl;
    std::cout<<averageAxonLength/numberOfRuns<<std::endl;
    if(targetReached>0){
    std::cout<<averageTargetAxonLength/targetReached<<std::endl;}
    std::cout<<"simulation finished"<<std::endl;
    return 0;

}
