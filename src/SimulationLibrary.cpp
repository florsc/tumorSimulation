//
// Created by florian on 9/10/21.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SimulationLibrary.h"
#include "Axon.h"
#include "helperFunctions.h"
#include "AxonManager.h"

using json = nlohmann::json;


int run() {
    std::cout << "Create spherical Limit" << std::endl;
    std::shared_ptr<SphericalLimit> sphericalLimit(new SphericalLimit(100));
    std::cout << "Create constraint Handle" << std::endl;
    std::shared_ptr<ConstraintHandler> constraintHandler(new ConstraintHandler(sphericalLimit));
    std::shared_ptr<ProcessSampler> processSampler(new biasedRandomWalk());
    std::cout << "Create Axon Manager" << std::endl;
    AxonManager axonManager(2, EuclideanVector({-1, -1, -1}), EuclideanVector({1, 1, 1}), constraintHandler,
                            processSampler);
    std::cout << "Run Axon growth" << std::endl;
    axonManager.run();
    std::vector<std::vector<std::vector<double>>> vec = axonManager.getAxonPositions();
    std::cout << "Create json" << std::endl;
    json j(vec);
    std::ofstream myfile;
    myfile.open("cpp_results.json");
    std::cout << "Write to file" << std::endl;
    myfile << j.dump();
    myfile.close();
    return 0;
}
