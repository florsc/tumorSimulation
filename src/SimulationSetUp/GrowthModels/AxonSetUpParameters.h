//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONSETUPPARAMETERS_H
#define TUMORSIMULATION_AXONSETUPPARAMETERS_H

#include "../../util/TypeDefs.h"

struct AxonSetUpParameters {
    double branchingProbability = 0.05;
    int maxNumberOfConstraintEncounters = 1000; //collision and contact to exterior limit
    int maxNumberOfBranches = 4;
    double maxAxonLength = 400;

    virtual ~AxonSetUpParameters() {}

    AxonSetUpParameters();
};

#endif //TUMORSIMULATION_AXONSETUPPARAMETERS_H
