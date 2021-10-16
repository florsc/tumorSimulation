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

class AxonOrder;

class Sampler;

class biasedRandomWalk;

class AxonFactory;

class ExteriorLimit;

class ConstraintManager;
class GrowthModel;
struct ParameterStruct {
    ParameterStruct();

    std::mt19937 m_generator = std::mt19937(
            std::chrono::system_clock::now().time_since_epoch().count());
    static constexpr int numberOfStartingAxons = 4;
    static constexpr double minDistance = 0.5;
    static constexpr double branchingProbability = 0.1;
    static constexpr double maximumTime = 10.0;
    static constexpr double angleThreshold = 0.7 * M_PI;
    std::pair<EuclideanVector, EuclideanVector> startingAreaCorners{{-10, -10, -10},
                                                                    {10,  10,  10}};
    std::unique_ptr<AxonOrder> axonOrder;
    std::unique_ptr<GrowthModel> growthModel;
    std::shared_ptr<ExteriorLimit> exteriorLimit;


};

extern ParameterStruct parameters;
#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
