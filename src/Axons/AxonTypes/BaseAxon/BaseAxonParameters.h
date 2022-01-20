//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_BASEAXONPARAMETERS_H
#define TUMORSIMULATION_BASEAXONPARAMETERS_H

#include "../../../SimulationSetUp/GrowthModels/AxonSetUpParameters.h"
class ParameterStruct;

struct BaseAxonParameters {

    const int maxNumberOfConstraintEncounters;
    double branchingProbability;
    int maxNumberOfBranches;
    int maxAxonLength;

    ConstraintManagerHandle constraintManager;
    TargetManagerHandle targetManager;
    SimulationManagerHandle simulationManager;

    explicit BaseAxonParameters(AxonSetUpParametersHandle axonSetUpParameters) : maxNumberOfConstraintEncounters(axonSetUpParameters->maxNumberOfConstraintEncounters),
                           branchingProbability(axonSetUpParameters->branchingProbability),maxNumberOfBranches(axonSetUpParameters->maxNumberOfBranches),maxAxonLength(axonSetUpParameters->maxAxonLength) {}
};

#endif //TUMORSIMULATION_BASEAXONPARAMETERS_H
