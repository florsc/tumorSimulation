//
// Created by florian on 9/22/21.
//

#include <iostream>
#include <utility>
#include "ParameterStruct.h"
#include "SimulationManager.h"

SimulationManager::SimulationManager(std::shared_ptr<ConstraintHandler> constraintHandler) : m_constraintHandler(
        std::move(constraintHandler)), m_axonManager(parameters.sampler->waitingTimeIsUsed()? std::unique_ptr<AxonManager>(new AxonManagerWaitingTime()):std::unique_ptr<AxonManager>(new AxonManagerNoWaitingTime())) {
    auto startPositions = sampleStartPositions(parameters.startingAreaCorners.first, parameters.startingAreaCorners.second);
    for (int i = 0; i < parameters.numberOfStartingAxons; i++) {
        auto startPositionIter = startPositions.begin();
        int startPositionIndex = parameters.sampler->getUniformSample() * (startPositions.size() - 1);
        std::advance(startPositionIter, startPositionIndex);
        addAxon(*startPositionIter);
        startPositions.erase(startPositionIter);

    }

}


std::list<EuclideanVector>
SimulationManager::sampleStartPositions(const EuclideanVector &c1, const EuclideanVector &c2) {
    double minDistance = parameters.minDistance;
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
                startPositions.push_back(EuclideanVector({xValue, yValue, zValue}));
            }
        }
    }
    return startPositions;
}

void SimulationManager::run() {
    while(auto axon = m_axonManager->getNextAxon()){
        axon->growthStep();
    }
}

std::vector<std::vector<std::vector<double>>> SimulationManager::getAxonPositions() {
    std::vector<std::vector<std::vector<double>>> axonVec;
    for (const auto &axon: m_axons) {
        auto &positionVec = axonVec.emplace_back();
        for (const auto &position: axon->getTipPositions()) {
            positionVec.push_back(std::vector<double>({position.at(0), position.at(1), position.at(2)}));
        }
    }
    return axonVec;
}

void SimulationManager::addAxon(const EuclideanVector& startPosition) {
    addAxon(
            std::make_shared<Axon>(m_axons.size(), startPosition, m_constraintHandler, *this));
}

void SimulationManager::addAxon(const EuclideanVector& startPosition, const EuclideanVector& direction) {
    addAxon(
            std::make_shared<Axon>(m_axons.size(), startPosition, startPosition + direction, m_constraintHandler, *this));

}

void SimulationManager::addAxon(std::shared_ptr<Axon> axon) {
    m_axons.push_back(axon);
    m_axonManager->addAxon(axon);
}