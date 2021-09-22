//
// Created by florian on 9/10/21.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SimulationLibrary.h"
#include "Axon.h"
#include "helperFunctions.h"

using json = nlohmann::json;


int run() {
    std::cout << "Create spherical Limit" << std::endl;
    std::shared_ptr<SphericalLimit> sphericalLimit(new SphericalLimit(100));
    std::cout << "Create constraint Handle" << std::endl;
    std::shared_ptr<ConstraintHandler> constraintHandler(new ConstraintHandler(sphericalLimit));
    auto startPositions = HelperFunctions::sampleStartPositions(EuclideanVector{-1, -1, -1}, EuclideanVector{1, 1, 1});
    std::cout << "Create Axon" << std::endl;
    Axon a(startPositions.at(0), constraintHandler);
    std::cout << "Run Axon growth" << std::endl;
    a.run();
    std::vector<std::vector<double>> vec;
    for (const auto &position: a.getTipPositions()) {
        vec.push_back(std::vector<double>({position.at(0), position.at(1), position.at(2)}));
    }
    std::cout << "Create json" << std::endl;
    json j(vec);
    std::ofstream myfile;
    myfile.open("cpp_results.json");
    std::cout << "Write to file" << std::endl;
    myfile << j.dump();
    myfile.close();
    return 0;
}
