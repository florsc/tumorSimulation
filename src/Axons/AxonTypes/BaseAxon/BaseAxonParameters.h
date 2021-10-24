//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_BASEAXONPARAMETERS_H
#define TUMORSIMULATION_BASEAXONPARAMETERS_H

#include "../../../SimulationSetUp/GrowthModels/AxonSetUpParameters.h"

struct BaseAxonParameters {

    const int maxNumberOfConstraintEncounters;
    const double branchingProbability;

    ConstraintManagerHandle constraintManager;
    TargetManagerHandle targetManager;
    SimulationManagerHandle simulationManager;

    BaseAxonParameters() : maxNumberOfConstraintEncounters(AxonSetUpParameters::maxNumberOfConstraintEncounters),
                           branchingProbability(AxonSetUpParameters::branchingProbability) {}
};

#endif //TUMORSIMULATION_BASEAXONPARAMETERS_H
