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
#include "SimulationSetUp/ParameterStruct.h"

using json = nlohmann::json;


int run() {
    std::cout << "Create spherical Limit" << std::endl;
    std::shared_ptr<SphericalLimit> sphericalLimit(new SphericalLimit(10));
    std::cout << "Create constraint Handle" << std::endl;
    std::shared_ptr<ConstraintManager> constraintHandler = std::make_shared<ConstraintManager>();
    std::shared_ptr<Sampler> processSampler(new biasedRandomWalk());
    std::cout << "Create Axon Manager" << std::endl;
    SimulationManager simulationManager(constraintHandler);
    std::cout << "Run Axon growth" << std::endl;
    simulationManager.run();

    std::vector<std::vector<std::vector<double>>> vec = simulationManager.getAxonPositions();
    std::cout << "Create json" << std::endl;
    json j(vec);
    std::ofstream myfile;
    myfile.open("cpp_results.json");
    std::cout << "Write to file" << std::endl;
    myfile << j.dump();
    myfile.close();
    return 0;
}
