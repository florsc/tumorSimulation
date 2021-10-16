//
// Created by florian on 9/10/21.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SimulationLibrary.h"
#include "Axon.h"
#include "util/HelperFunctions.h"
#include "Managers/SimulationManager.h"


int run() {
    std::cout << "Create Simulation Manager" << std::endl;
    SimulationManager simulationManager;
    std::cout << "Run Axon growth" << std::endl;
    simulationManager.run();

    std::vector<std::vector<std::vector<double>>> vec = simulationManager.getAxonPositions();
    std::cout << "Create json" << std::endl;
    nlohmann::json j(vec);
    std::ofstream myfile;
    myfile.open("cpp_results.json");
    std::cout << "Write to file" << std::endl;
    myfile << j.dump();
    myfile.close();
    return 0;
}
