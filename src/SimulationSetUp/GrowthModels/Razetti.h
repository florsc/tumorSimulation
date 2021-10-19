//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_RAZETTI_H
#define TUMORSIMULATION_RAZETTI_H
#include "GrowthModel.h"
#include "../../util/Samplers.h"

class Razetti:public GrowthModel {

    const int numberOfGrowthStepsEachTimeStep = 6;
    const int numberOfRetractions = 2;
    const int maxNumberOfConstraintEncounters = 100;
    const double alpha = 1;
    const double beta = 0;
    SamplerHandle lengthSampler = std::make_shared<ConstantValueSampler>(1);

public:
    Razetti():GrowthModel(){}
    AxonFactoryHandle makeAxonFactory(SimulationManagerHandle simulationManager) override;
};


#endif //TUMORSIMULATION_RAZETTI_H
