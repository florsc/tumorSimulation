//
// Created by florian on 9/9/21.
//

#include <iostream>
#include "Axon.h"
#include "HelperFunctions.h"

Axon::Axon(int identifier, EuclideanVector startPosition, std::shared_ptr<ConstraintHandler> constraintHandler,
           SimulationManager &axonManager) : m_identifier(identifier), m_constraintHandler(
        constraintHandler), m_AxonManager(axonManager) {
    m_tipPositions.push_back(startPosition);
}

Axon::Axon(int identifier, EuclideanVector startPosition, EuclideanVector nextPosition,
           std::shared_ptr<ConstraintHandler> constraintHandler, SimulationManager &axonManager) : m_identifier(
        identifier), m_constraintHandler(
        constraintHandler), m_AxonManager(axonManager) {
    m_tipPositions.push_back(startPosition);
    m_tipPositions.push_back(nextPosition);
}

std::vector<EuclideanVector> Axon::createCenters(const EuclideanVector &start, const EuclideanVector &diff) {
    double centerDistance = parameters.minDistance;
    double length = diff.GetEuclideanNorm();
    if (length > centerDistance) {
        int numberOfCenters = floor(length / centerDistance);
        std::vector<EuclideanVector> res = std::vector<EuclideanVector>();
        for (int i = 1; i <= numberOfCenters; i++) {
            res.emplace_back(EuclideanVector(start + diff * (double(i) / double(numberOfCenters))));
        }
        return res;
    }
    return {};
}

bool
Axon::checkForBackwardGrowth(const EuclideanVector &oldVector, const EuclideanVector &newVector, double threshold) {
    double tmp = M_PI -
                 std::acos(oldVector.CreateUnitVector() * newVector);
    return tmp < threshold;
}

void Axon::createNewBranch() {
    auto size = m_tipPositions.size();
    auto crossProductVector = crossProduct(m_tipPositions.at(size - 1) - m_tipPositions.at(size - 2),
                                           m_tipPositions.at(size - 2) - m_tipPositions.at(size - 3));
    m_AxonManager.addAxon(m_tipPositions.at(size - 1), parameters.minDistance * crossProductVector.CreateUnitVector());
}

EuclideanVector Axon::sampleVector() {
    return EuclideanVector({parameters.sampler->getNormalSample(), parameters.sampler->getNormalSample(),
                            parameters.sampler->getNormalSample()}).CreateUnitVector();
}

void Axon::growthStep() {
    auto vec = sampleVector();
    if (m_tipPositions.size() > 1) {
        auto lastVector = m_tipPositions.back() - m_tipPositions.at(m_tipPositions.size() - 2);
        while (checkForBackwardGrowth(lastVector, vec, parameters.angleThreshold)) {
            vec = sampleVector();
        }
    }
    auto centers = createCenters(m_tipPositions.back(), vec);
    for(const auto center:centers){
    }
    if (!m_constraintHandler->checkForConstraint(centers)) {
        m_tipPositions.emplace_back(m_tipPositions.back() + vec);

        if (parameters.sampler->branch() && m_tipPositions.size() > 3) {
            createNewBranch();
        }
    } else {
        m_constraintCounter++;
        if (m_constraintCounter > parameters.numberOfAllowedConstraints) { stopAxon(); }
    }
}
bool Axon::isActive() const  { return m_active; }

