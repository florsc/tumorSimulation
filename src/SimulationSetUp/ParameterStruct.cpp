//
// Created by florian on 9/29/21.
//

#include <fstream>
#include "ParameterStruct.h"
#include "GrowthModels/RazettiSetUpParameters.h"
#include "GrowthModels/RandomDirectionSetUpParameters.h"
#include "AxonOrder/AxonOrderSampledWaitingTimeData.h"
#include "TargetSetUp/SphericalTargetSetUpParameters.h"
#include "AxonOrder/AxonOrderLinearData.h"


ParameterStruct::ParameterStruct() {

    m_generator = GeneratorSingleton::getInstance()->m_generator; //ignore this, will be set automatically

    //Exterior Limit
    exteriorLimitSetUpParameters = nullptr; //Possibility to set extern constraints, currently a sphere is possible

    //Axon order
    axonOrderData = std::make_shared<AxonOrderLinearData>(); //Replace AxonOrderLinearData by AxonOrderSampleWaitingTimeData when axons should grow at random times instead of one after another

    //AxonParameters
    axonSetUpParameters = std::make_shared<RazettiSetUpParameters>(); //Growth model, look into the respective files for more details

    numberOfStartingAxons = 1;

    minDistance = 0.1; //minimal distance between to axons before a collision is detected
    startDistance = 2; //minimal distance between to axons at start, irrelevant with one axon
    startingAreaCorners = std::pair<EuclideanVector, EuclideanVector>{{-5, -5, -5},
                                                                      {5,  5,  5}}; //corners of a cube from which the start positions are sampled
}

//samples random targets in a sphere with radius of maximum axon length around the origin, mass is the collective volume of all targets
void ParameterStruct::createRandomTargets(int minTargets, int maxTargets, double mass) {
    targets = TargetSetUpVector();
    auto targetNumber = std::uniform_int_distribution<int>(minTargets, maxTargets)(*m_generator);
    double radius = pow((mass / targetNumber) * 0.75 / M_PI, (1.0 / 3.0));
    double limitRadius = axonSetUpParameters->maxAxonLength;
    auto sampler = std::uniform_real_distribution(radius - limitRadius, limitRadius - radius);
    double minDistanceFromOrigin = 5;
    for (int i = 0; i < targetNumber; i++) {

        auto centerPoint = EuclideanVector(sampler(*m_generator), sampler(*m_generator),
                                           sampler(*m_generator));
        while (centerPoint.GetEuclideanNorm() > limitRadius - radius &&
               centerPoint.GetEuclideanNorm() < minDistanceFromOrigin + radius) {
            centerPoint = EuclideanVector(sampler(*m_generator), sampler(*m_generator),
                                          sampler(*m_generator));
        }
        auto targetSetUpHandle = std::make_shared<SphericalTargetSetUpParameters>();
        targetSetUpHandle->centerPoint = centerPoint;
        targetSetUpHandle->radius = radius;
        targets.push_back(targetSetUpHandle);
    }
}

