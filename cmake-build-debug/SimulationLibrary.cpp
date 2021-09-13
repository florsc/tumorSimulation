//
// Created by florian on 9/10/21.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SimulationLibrary.h"
#include "Axon.h"

using json = nlohmann::json;


int run(){
    Axon a;
    a.run();
    json j(a.getTipPositions());
        std::ofstream myfile;
        myfile.open ("cpp_results.json");
        myfile << j.dump();
        myfile.close();
    return 4;
}
