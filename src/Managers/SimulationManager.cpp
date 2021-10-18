//
// Created by florian on 9/22/21.
//

#include <iostream>
#include <utility>
#include <random>
#include "../SimulationSetUp/ParameterStruct.h"
#include "SimulationManager.h"
#include "AxonManagers/AxonManager.h"
#include "../Sampler.h"
#include "../Axons/AxonTypes/RazettiAxon.h"
#include "../Axons/Factories/AxonFactory.h"
#include "../SimulationSetUp/GrowthModels/GrowthModel.h"
#include "../SimulationSetUp/AxonOrder/AxonOrder.h"
#include "../SimulationSetUp/AxonOrder/AxonOrderSampledWaitingTime.h"

SimulationManager::SimulationManager() {

}

void SimulationManager::setUp(SimulationManagerHandle  simulationManager){
    m_axonManager = std::move(parameters.axonOrder->makeAxonManager());
    m_axonFactory = std::move(parameters.growthModel->makeAxonFactory(simulationManager));

    auto startPositions = createPossibleStartPositions(parameters.startingAreaCorners.first,
                                                       parameters.startingAreaCorners.second, parameters.minDistance);
    for (int i = 0; i < parameters.numberOfStartingAxons; i++) {
        auto startPositionIter = startPositions.begin();
        auto indexSampler = std::uniform_int_distribution<int>(0, startPositions.size() - 1);
        int startPositionIndex = indexSampler(parameters.m_generator);
        std::advance(startPositionIter, startPositionIndex);
        addAxon(*startPositionIter);
        startPositions.erase(startPositionIter);
    }
}


std::list<EuclideanVector>
SimulationManager::createPossibleStartPositions(const EuclideanVector &c1, const EuclideanVector &c2,
                                                double minDistance) {
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

std::vector<std::vector<std::vector<double>>> SimulationManager::getAxonPositions() {
    std::vector<std::vector<std::vector<double>>> axonVec;
    for (const auto &axon: m_axonManager->getAllAxons()) {
        auto &positionVec = axonVec.emplace_back();
        for (const auto &position: axon->getTipPositions()) {
            positionVec.push_back(std::vector<double>({position.at(0), position.at(1), position.at(2)}));
        }
    }
    return axonVec;
}

void SimulationManager::addAxon(const EuclideanVector &startPosition) {
    addAxon(m_axonFactory->makeAxon(startPosition));
}

void SimulationManager::addStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) {
    addAxon(m_axonFactory->makeStartedAxon(startPosition, nextPosition));
}

void SimulationManager::addAxon(AxonHandle axon) {
    m_axonManager->addAxon(axon);
}

SimulationManager::~SimulationManager() { std::cout << "SimulationManager destructed" << std::endl; }

void SimulationManager::removeAxon(const int id) {
    m_axonManager->removeAxon(id);
}
