//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONSETUPPARAMETERS_H
#define TUMORSIMULATION_AXONSETUPPARAMETERS_H

#include "../../util/TypeDefs.h"

struct AxonSetUpParameters {
    static constexpr double branchingProbability = 0.01;
    static constexpr int maxNumberOfConstraintEncounters = 10;
};

#endif //TUMORSIMULATION_AXONSETUPPARAMETERS_H
