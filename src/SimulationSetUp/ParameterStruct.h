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
#include "../Axons/Factories/RandomDirectionFactory.h"

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

    long long seed =std::chrono::system_clock::now().time_since_epoch().count();
    GeneratorHandle m_generator;
    static constexpr int maxNumberOfBranches =20;
    static constexpr int exteriorLimitRadius = 400;
    static constexpr int numberOfStartingAxons = 1;
    static constexpr double minDistance = 0.1;
    static constexpr double startDistance = 2;
    static constexpr double maxAxonLength = 400;
    std::pair<EuclideanVector, EuclideanVector> startingAreaCorners{{-5, -5, -5},
                                                                    {5,  5,  5}};
    std::unique_ptr<AxonOrder> axonOrder;
    std::shared_ptr<ExteriorLimit> exteriorLimit;
    double radius = 5;
    std::pair<double, double> startAngles;
    TargetVector targets;
    PositionVector targetPositions;
    AxonFactoryHandle makeAxonFactory();
    std::shared_ptr<ExteriorLimit> getExteriorLimit();
    TargetVector getTargets();

    void createRandomTargets(int minTargets, int maxTargets, double mass);

    void createFixTargets();

    void createStartAngles();
};

extern ParameterStruct parameters;
#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
