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
#include "../util/GeneratorSingleton.h"
#include "GrowthModels/RandomDirectionSetUpParameters.h"
#include "GrowthModels/RazettiSetUpParameters.h"
#include "AxonOrder/AxonOrderLinearData.h"
#include "AxonOrder/AxonOrderSampledWaitingTimeData.h"
#include "AxonOrder/AxonOrderData.h"

class AxonOrderData;

class Sampler;

class biasedRandomWalk;

class AxonFactory;

class ExteriorLimit;

class ConstraintManager;

class AxonSetUpParameters;

struct ParameterStruct {
    ParameterStruct();

    GeneratorHandle m_generator;

    //Exterior Limit
    ExteriorLimitSetUpParametersHandle exteriorLimitSetUpParameters;

    //Axon order
    AxonOrderDataHandle axonOrderData;


    //AxonParameters
    AxonSetUpParametersHandle axonSetUpParameters;


    int numberOfStartingAxons;
    double minDistance;
    double startDistance;
    std::pair<EuclideanVector, EuclideanVector> startingAreaCorners;
    TargetSetUpVector targets;

    void createRandomTargets(int minTargets, int maxTargets, double mass);


};

#endif //TUMORSIMULATION_PARAMETERSTRUCT_H
