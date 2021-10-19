//
// Created by florian on 9/10/21.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SimulationLibrary.h"
#include "util/HelperFunctions.h"
#include "Managers/SimulationManager.h"


int run() {
    std::cout << "Create Simulation Manager" << std::endl;
    auto simulationManager = std::make_shared<SimulationManager>();
    std::cout << "Set up simulation" << std::endl;
    simulationManager->setUp(simulationManager);
    std::cout << "Run Axon growth" << std::endl;
    simulationManager->run();

    std::vector<std::vector<std::vector<double>>> vec = simulationManager->getAxonPositions();
    std::cout << "Create json" << std::endl;
    nlohmann::json j(vec);
    std::ofstream myfile;
    myfile.open("cpp_results.json");
    std::cout << "Write to file" << std::endl;
    myfile << j.dump();
    myfile.close();
    return 0;
}
