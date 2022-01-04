//
// Created by florian on 9/22/21.
//

#include <iostream>
#include <utility>
#include <random>
#include "../SimulationSetUp/ParameterStruct.h"
#include "SimulationManager.h"
#include "AxonManagers/AxonManager.h"
#include "../Axons/AxonTypes/RazettiAxon/RazettiAxon.h"
#include "../Axons/Factories/AxonFactory.h"
#include "../SimulationSetUp/GrowthModels/AxonSetUpParameters.h"
#include "../SimulationSetUp/AxonOrder/AxonOrder.h"
#include "../SimulationSetUp/AxonOrder/AxonOrderSampledWaitingTime.h"


void SimulationManager::setUp(SimulationManagerHandle simulationManager,double branchingProbability) {
    m_axonManager = std::move(parameters.axonOrder->makeAxonManager());
    m_axonFactory = std::move(parameters.makeAxonFactory());
    m_axonFactory->setUpFactory(std::move(simulationManager), branchingProbability);
    auto startPositions = createPossibleStartPositions(parameters.startingAreaCorners.first,
                                                       parameters.startingAreaCorners.second, ParameterStruct::startDistance);
    for (int i = 0; i < ParameterStruct::numberOfStartingAxons; i++) {
        auto startPositionIter = startPositions.begin();
        auto indexSampler = std::uniform_int_distribution<int>(0, startPositions.size() - 1);
        int startPositionIndex = indexSampler(*parameters.m_generator);
        std::advance(startPositionIter, startPositionIndex);
        addAxon(*startPositionIter);
        startPositions.erase(startPositionIter);
    }
}


PositionList
SimulationManager::createPossibleStartPositions(const EuclideanVector &c1, const EuclideanVector &c2,
                                                double minDistance)  {
    auto diff = c2 - c1;
    std::vector<std::vector<double>> spacedAxisValues;
    for (int i = 0; i < 3; i++) {
        spacedAxisValues.emplace_back();
        if (diff.at(i) <= minDistance) {
            spacedAxisValues.at(i).push_back(c1.at(i) + diff.at(i) / 2);
        } else {
            int numberOfPositions = ceil(diff.at(i) / minDistance);
            double equalSpace = diff.at(i) / (numberOfPositions - 1);
            for (int j = 0; j < numberOfPositions; j++) {
                spacedAxisValues.at(i).push_back(c1.at(i) + j * equalSpace);
            }
        }
    }
    std::list<EuclideanVector> startPositions;
    for (const auto &xValue: spacedAxisValues.at(0)) {
        for (const auto &yValue: spacedAxisValues.at(1)) {
            for (const auto &zValue: spacedAxisValues.at(2)) {
                startPositions.emplace_back(xValue, yValue, zValue);
            }
        }
    }
    return startPositions;
}

void SimulationManager::run() {
    while (auto axon = m_axonManager->getNextAxon()) {
        axon->grow();
    }
}

std::vector<std::vector<std::vector<double>>> SimulationManager::getAxonPositions()  const{
    std::vector<std::vector<std::vector<double>>> axonVec;
    for (const auto &axon: m_axonManager->getAllAxons()) {
        auto &positionVec = axonVec.emplace_back();
        for (const auto &position: axon->getTipPositions()) {
            positionVec.push_back(std::vector<double>({position.at(0), position.at(1), position.at(2)}));
        }
    }
    return axonVec;
}

AxonHandle
SimulationManager::addAxon(const EuclideanVector &startPosition, int constraintsEncountered, WeakAxonHandle rootAxon) {
    auto newAxon = (m_axonFactory->makeAxon(startPosition, constraintsEncountered, rootAxon));
    addAxon(newAxon);
    return newAxon;
}

AxonHandle
SimulationManager::addStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                                  int constraintsEncountered, WeakAxonHandle rootAxon) {
    auto newAxon = m_axonFactory->makeStartedAxon(startPosition, nextPosition, constraintsEncountered, rootAxon);
    addAxon(newAxon);
    return newAxon;
}

void SimulationManager::addAxon(AxonHandle axon) {
    m_axonManager->addAxon(std::move(axon));
}

void SimulationManager::removeAxon(const int id) {
    m_axonManager->removeAxon(id);
}

int SimulationManager::getNumberOfTargetReached() {
    int targetsReached = 0;
    auto allAxons = m_axonManager->getAllAxons();
    for(const auto& axon:allAxons){
        if(axon->getId()<ParameterStruct::numberOfStartingAxons && axon->targetIsReached()){
            targetsReached++;
        }
    }
    return targetsReached;
}

double SimulationManager::getAxonLength() {
    double length = 0;
    auto allAxons = m_axonManager->getAllAxons();
    for(const auto& axon:allAxons){
        if(axon->getId()<ParameterStruct::numberOfStartingAxons){
            length += axon->getBranchLength();
        }
    }
    return length;
}

double SimulationManager::getNumberOfAxons() {
    return m_axonManager->getAllAxons().size();
}
