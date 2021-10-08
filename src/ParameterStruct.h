//
// Created by florian on 9/28/21.
//

#ifndef TUMORSIMULATION_PARAMETERSTRUCT_H
#define TUMORSIMULATION_PARAMETERSTRUCT_H

#include "Sampler.h"
#include <memory>
#include <cmath>
#include "EuclideanVector.h"
#include "ExteriorLimit.h"
#include "ConstraintHandler.h"

class Sampler;
class biasedRandomWalk;

struct ParameterStruct {
    ParameterStruct();
    int numberOfStartingAxons = 4;
    double minDistance = 0.1;
    double branchingProbability = 0.1;
    double maximumTime = 10.0;
    double numberOfAllowedConstraints = 10;
    double angleThreshold = 0.7 * M_PI;
    std::pair<EuclideanVector, EuclideanVector> startingAreaCorners{{-10,-10,-10}, {10,10,10}};
    std::unique_ptr<Sampler> sampler;
    std::unique_ptr<ExteriorLimit> exteriorLimit = std::make_unique<SphericalLimit>(100);


};
extern ParameterStruct parameters;
#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
