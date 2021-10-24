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
#include "../util/TypeDefs.h"
#include "GrowthModels/RandomDirectionSetUpParameters.h"
#include "../Axons/Factories/RazettiFactory.h"

class AxonOrder;

class Sampler;

class biasedRandomWalk;

class AxonFactory;

class ExteriorLimit;

class ConstraintManager;

class AxonSetUpParameters;

struct ParameterStruct {
    ParameterStruct();

    void init();

    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    GeneratorHandle m_generator;
    static constexpr int numberOfStartingAxons = 4;
    static constexpr double minDistance = 0.3;
    std::pair<EuclideanVector, EuclideanVector> startingAreaCorners{{-10, -10, -10},
                                                                    {10,  10,  10}};
    std::unique_ptr<AxonOrder> axonOrder;
    std::unique_ptr<RazettiFactory> axonFactory;
    std::shared_ptr<ExteriorLimit> exteriorLimit;
    TargetVector targets;
};

extern ParameterStruct parameters;
#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
