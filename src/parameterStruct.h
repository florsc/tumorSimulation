//
// Created by florian on 9/28/21.
//

#ifndef TUMORSIMULATION_PARAMETERSTRUCT_H
#define TUMORSIMULATION_PARAMETERSTRUCT_H
#include "ProcessSampler.h"

 extern struct {
    int numberOfStartingAxons = 2;
    double minDistance = 0.1;
    double branchingProbability = 0.3;
    //auto sampler = std::make_shared<biasedRandomWalk>();

} parameterStruct;
#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
