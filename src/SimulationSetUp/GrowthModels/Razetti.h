//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_RAZETTI_H
#define TUMORSIMULATION_RAZETTI_H
#include "GrowthModel.h"

class Razetti:public GrowthModel {

    const int numberOfGrowthStepsEachTimeStep = 6;
    const int numberOfRetractions = 2;
    const int maxNumberOfConstraintEncounters = 100;
    const double alpha = 1;
    const double beta = 0;
    const double stepLength = 1;

public:
    Razetti():GrowthModel(){}
    AxonFactoryHandle makeAxonFactory(SimulationManagerHandle simulationManager) override;
};


#endif //TUMORSIMULATION_RAZETTI_H
