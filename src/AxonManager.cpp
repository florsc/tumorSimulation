//
// Created by florian on 9/22/21.
//

#include <iostream>
#include "AxonManager.h"

AxonManager::AxonManager(int numberOfStartingAxons, EuclideanVector cornerStartingArea1,
                         EuclideanVector cornerStartingArea2,
                         std::shared_ptr<ConstraintHandler> constraintHandler,
                         std::shared_ptr<ProcessSampler> processSampler) : m_constraintHandler(constraintHandler),
                                                                           m_processSampler(processSampler) {
    m_startPositions = sampleStartPositions(cornerStartingArea1, cornerStartingArea2);
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < numberOfStartingAxons; i++) {
        std::uniform_int_distribution<> distrib(0, m_startPositions.size() - 1);
        auto startPositionIter = m_startPositions.begin();
        int startPositionIndex = distrib(gen);
        std::advance(startPositionIter, startPositionIndex);
        m_axons.push_back(std::shared_ptr<Axon>(
                new Axon(m_axons.size(), *startPositionIter, m_constraintHandler, m_processSampler)));
        m_startPositions.erase(startPositionIter);
    }

    if (m_processSampler->sampleWaitingTime()) {
        for(int i = 0; i<m_axons.size();i++){
            m_processSampler->addAxon(i);
        }}
}


std::list<EuclideanVector> AxonManager::sampleStartPositions(EuclideanVector c1, EuclideanVector c2) {
    double minDistance = 0.1;
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

void AxonManager::run() {
    if (m_processSampler->sampleWaitingTime()) {
        for (int i = 0; i < 10; i++) {
            auto axonTimeIndex = m_processSampler->getNextAxon();
            m_axons.at(axonTimeIndex.second)->growthStep();
            m_processSampler->addAxon(axonTimeIndex.first, axonTimeIndex.second);
        }
    } else {
        for (int i = 0; i < 10; i++) {
            for (const auto &axon: m_axons) {
                axon->growthStep();
            }
        }
    }
}

std::vector<std::vector<std::vector<double>>> AxonManager::getAxonPositions() {
    std::vector<std::vector<std::vector<double>>> axonVec;
    for (const auto &axon: m_axons) {
        auto &positionVec = axonVec.emplace_back();
        for (const auto &position: axon->getTipPositions()) {
            positionVec.push_back(std::vector<double>({position.at(0), position.at(1), position.at(2)}));
        }
    }
    return axonVec;
}

void AxonManager::addAxon(EuclideanVector startPosition) {
    m_axons.push_back(
            std::shared_ptr<Axon>(new Axon(m_axons.size(), startPosition, m_constraintHandler, m_processSampler)));
}
