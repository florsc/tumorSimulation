//
// Created by florian on 9/29/21.
//

#include <fstream>
#include "ParameterStruct.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include "GrowthModels/Razetti.h"
#include "GrowthModels/RandomDirection.h"
#include "AxonOrder/AxonOrderSampledWaitingTime.h"

ParameterStruct::ParameterStruct() : m_generator (new std::mt19937(seed)),
exteriorLimit(new SphericalLimit(40)),
                                     growthModel(new RandomDirection()),
                                     axonOrder(new AxonOrderSampledWaitingTime()) {

    std::ofstream seedFile;
    seedFile.open ("seeds.txt", std::ios_base::app);
    seedFile << seed<<"\n";
    seedFile.close();
}

ParameterStruct parameters;