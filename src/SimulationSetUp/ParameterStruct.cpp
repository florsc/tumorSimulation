//
// Created by florian on 9/29/21.
//

#include <fstream>
#include "ParameterStruct.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include "GrowthModels/RazettiSetUpParameters.h"
#include "GrowthModels/RandomDirectionSetUpParameters.h"
#include "AxonOrder/AxonOrderSampledWaitingTime.h"
#include "../Targets/SphericalTarget.h"
#include "../Axons/Factories/RandomDirectionFactory.h"
#include "AxonOrder/AxonOrderLinear.h"

ParameterStruct::ParameterStruct() : m_generator(new std::mt19937(
        seed)) {
    std::ofstream seedFile;
    seedFile.open("seeds.txt", std::ios_base::app);
    seedFile << seed << "\n";
    seedFile.close();
}

void ParameterStruct::init() {
    exteriorLimit = std::shared_ptr<ExteriorLimit>(new SphericalLimit(100));
    axonOrder = std::make_unique<AxonOrderLinear>();/*
    targets = TargetVector();
    for(double i1:{-60,60}){
        for(double i2:{-60,60}){
            for(double i3:{-60,60}) {
                targets.emplace_back(new SphericalTarget({i1, i2, i3}, 30,100));
            }}            }*/
}

AxonFactoryHandle ParameterStruct::makeAxonFactory() {
    return std::make_shared<RazettiFactory>();
}

std::shared_ptr<ExteriorLimit> ParameterStruct::getExteriorLimit() {
    exteriorLimit = std::shared_ptr<ExteriorLimit>(new SphericalLimit(exteriorLimitRadius));
    return exteriorLimit;
}

void ParameterStruct::createFixTargets(){
    PositionVector positions = PositionVector ();
    auto pos = 40;
    for(double i1:{-pos,pos}){
        for(double i2:{-pos,pos}){
            for(double i3:{-pos,pos}) {
                positions.emplace_back(i1, i2, i3);
            }}            }
    targetPositions = positions;
}

void ParameterStruct::createRandomTargets(int minTargets, int maxTargets, double mass){
    PositionVector positions = PositionVector ();
    auto targetNumber = std::uniform_int_distribution<int>(minTargets, maxTargets)(*m_generator);
    radius = pow((mass/targetNumber)*0.75/M_PI,(1.0/3.0));
    double limitRadius = 400;
    auto sampler = std::uniform_real_distribution(radius-limitRadius, limitRadius-radius);
    /*std::normal_distribution<double> normalDistribution{0, 1};
    for(int i = 0;i<targetNumber;i++){
        auto unitVector = EuclideanVector(normalDistribution(*m_generator), normalDistribution(*m_generator),
                               normalDistribution(*m_generator)).CreateUnitVector();
    targetPositions.push_back(unitVector*sampler(*m_generator));
    */

    for(int i = 0;i<targetNumber;i++){

        auto unitVector = EuclideanVector(sampler(*m_generator), sampler(*m_generator),
                                          sampler(*m_generator));
        while(unitVector.GetEuclideanNorm()>limitRadius-radius &&unitVector.GetEuclideanNorm()<5+radius){
            unitVector = EuclideanVector(sampler(*m_generator), sampler(*m_generator),
                                              sampler(*m_generator));
        }
        positions.push_back(unitVector);
    }
    targetPositions = positions;
}

void ParameterStruct::createStartAngles(){
    startAngles = std::make_pair<double, double>(std::uniform_real_distribution<>(0.0, M_PI)(*m_generator), std::uniform_real_distribution<>(0.0, 2*M_PI)(*m_generator));
}
TargetVector ParameterStruct::getTargets() {
    TargetVector localTargets = TargetVector();
    for(const auto& targetPosition:targetPositions) {
        localTargets.emplace_back(new SphericalTarget(targetPosition, radius, 1));
    }
    targets = localTargets;
    return targets;
}

ParameterStruct parameters;