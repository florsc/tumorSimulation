//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONSETUPPARAMETERS_H
#define TUMORSIMULATION_AXONSETUPPARAMETERS_H

#include "../../util/TypeDefs.h"

struct AxonSetUpParameters {
    static constexpr double branchingProbability = 0.05;
    static constexpr int maxNumberOfConstraintEncounters = 1000;
};

#endif //TUMORSIMULATION_AXONSETUPPARAMETERS_H
