//
// Created by florian on 9/29/21.
//

#include <fstream>
#include "ParameterStruct.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include "GrowthModels/RazettiSetUpParameters.h"
#include "GrowthModels/RandomDirectionSetUpParameters.h"
#include "AxonOrder/AxonOrderSampledWaitingTimeData.h"
#include "../Targets/SphericalTarget.h"
#include "TargetSetUp/SphericalTargetSetUpParameters.h"
#include "../Axons/Factories/RandomDirectionFactory.h"
#include "AxonOrder/AxonOrderLinearData.h"


ParameterStruct::ParameterStruct(){

    m_generator = GeneratorSingleton::getInstance()->m_generator;

    //Exterior Limit
    exteriorLimitSetUpParameters = nullptr;

    //Axon order
    axonOrderData = std::make_shared<AxonOrderLinearData>();

    //AxonParameters
    axonSetUpParameters = std::make_shared<RazettiSetUpParameters>();

    numberOfStartingAxons = 1;
    minDistance = 0.1;
    startDistance = 2;
    startingAreaCorners = std::pair<EuclideanVector, EuclideanVector> {{-5, -5, -5},
                                                                    {5,  5,  5}};
}



void ParameterStruct::createRandomTargets(int minTargets, int maxTargets, double mass){
    targets = TargetSetUpVector();
    auto targetNumber = std::uniform_int_distribution<int>(minTargets, maxTargets)(*m_generator);
    double radius = pow((mass/targetNumber)*0.75/M_PI,(1.0/3.0));
    double limitRadius = 400;
    auto sampler = std::uniform_real_distribution(radius-limitRadius, limitRadius-radius);

    for(int i = 0;i<targetNumber;i++){

        auto centerPoint = EuclideanVector(sampler(*m_generator), sampler(*m_generator),
                                          sampler(*m_generator));
        while(centerPoint.GetEuclideanNorm()>limitRadius-radius &&centerPoint.GetEuclideanNorm()<5+radius){
            centerPoint = EuclideanVector(sampler(*m_generator), sampler(*m_generator),
                                              sampler(*m_generator));
        }
        auto targetSetUpHandle = std::make_shared<SphericalTargetSetUpParameters>();
        targetSetUpHandle->centerPoint = centerPoint;
        targetSetUpHandle->radius=radius;
        targets.push_back(targetSetUpHandle);
    }
}
