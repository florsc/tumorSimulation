//
// Created by florian on 9/28/21.
//

#ifndef TUMORSIMULATION_PARAMETERSTRUCT_H
#define TUMORSIMULATION_PARAMETERSTRUCT_H

#include <random>
#include <memory>
#include <cmath>
#include <chrono>
#include "../util/EuclideanVector.h"
#include "../ExteriorLimits/ExteriorLimit.h"

class Sampler;

class biasedRandomWalk;

class ConstraintManager;

struct ParameterStruct {
    ParameterStruct();

    int numberOfStartingAxons = 4;
    double minDistance = 0.5;
    double branchingProbability = 0.1;
    double maximumTime = 10.0;
    double numberOfAllowedConstraints = 10;
    double angleThreshold = 0.7 * M_PI;
    std::pair<EuclideanVector, EuclideanVector> startingAreaCorners{{-10, -10, -10},
                                                                    {10,  10,  10}};
    std::unique_ptr<Sampler> sampler;
    std::unique_ptr<ExteriorLimit> exteriorLimit = std::make_unique<SphericalLimit>(30);
    std::mt19937 generator = std::mt19937(
            std::chrono::system_clock::now().time_since_epoch().count());


};

extern ParameterStruct parameters;
#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
