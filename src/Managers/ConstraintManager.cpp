//
// Created by florian on 9/9/21.
//

#include <memory>
#include <iostream>
#include "ConstraintManager.h"
#include <algorithm>
#include "../ExteriorLimits/ExteriorLimit.h"
#include "../SimulationSetUp/ParameterStruct.h"

bool ConstraintManager::checkForExteriorLimit(const EuclideanVector &position) {
    return m_exteriorLimit->checkExteriorLimitExceeded(position);
}

bool ConstraintManager::checkForConstraint(const std::vector<EuclideanVector> &positions, int axonIdentifier,
                                           int growthStep) {
    if (!checkForExteriorLimit(positions.back())) {
        return checkForOccupiedSpace(positions, axonIdentifier, growthStep, true);
    }
    return true;
}

bool ConstraintManager::checkForConstraint(const std::vector<EuclideanVector> &positions) {
    if (!checkForExteriorLimit(positions.back())) {
        return checkForOccupiedSpace(positions, 0, 0, false);
    }
    return true;
}

bool ConstraintManager::checkForOccupiedSpace(const std::vector<EuclideanVector> &positions, int axonIdentifier,
                                              int growthStep, bool addCenters) {
    if (!m_centerMap.empty()) {
        double low = std::min(positions.at(0).at(0), positions.back().at(0));
        double high = std::max(positions.at(0).at(0), positions.back().at(0));
        auto itLow = m_centerMap.lower_bound(low - m_distanceLimit);
        auto itHigh = m_centerMap.lower_bound(high + m_distanceLimit);
        auto itLowTmp = itLow;
        double distanceLimitSquared = m_distanceLimit * m_distanceLimit;
        while (itLowTmp != itHigh) {
            auto center = itLowTmp->second.first;
            for (const auto &position: positions) {
                if ((position - center) * (position - center) < distanceLimitSquared) {
                    return true;
                }
            }
            itLowTmp++;
        }
        if (addCenters) {
            auto itPos = positions.begin();
            while (itPos != positions.end()) {
                while (itLow != itHigh && itLow->first < itPos->at(0)) {
                    itLow++;
                }

                m_centerMap.insert(
                        std::make_pair(itPos->at(0),
                                       std::make_pair(*itPos, std::make_pair(axonIdentifier, growthStep))));
                itPos++;
            }
        }
    } else { addConstraintCenters(positions); }
    return false;
}

ConstraintManager::ConstraintManager() : m_exteriorLimit(parameters.exteriorLimit),
                                         m_distanceLimit(parameters.minDistance) {

}

ConstraintManager::ConstraintManager(std::shared_ptr<ExteriorLimit> exteriorLimit, double distanceLimit)
        : m_exteriorLimit(exteriorLimit), m_distanceLimit(distanceLimit) {

}

void ConstraintManager::addConstraintCenters(const std::vector<EuclideanVector> &constraintCenters, int axonIdentifier,
                                             int growthStep) {
    for (const auto &constraintCenter: constraintCenters) {
        m_centerMap.insert(std::make_pair(constraintCenter.at(0), std::make_pair(constraintCenter,
                                                                                 std::make_pair(axonIdentifier,
                                                                                                growthStep))));
    }
}

void ConstraintManager::freeSpace(int axonIdentifier, std::initializer_list<int> growthSteps) {

    for (auto it = m_centerMap.begin(); it != m_centerMap.end(); it++) {
        if (it->second.second.first == axonIdentifier) {
            if (std::find(growthSteps.begin(), growthSteps.end(), it->second.second.second) != growthSteps.end()) {
                m_centerMap.erase(it);
            }
        }
    }
}

void ConstraintManager::addConstraintCenters(const std::list<EuclideanVector> &constraintCenters, int axonIdentifier,
                                             int growthStep) {

    for (const auto &constraintCenter: constraintCenters) {
        m_centerMap.insert(std::make_pair(constraintCenter.at(0), std::make_pair(constraintCenter,
                                                                                 std::make_pair(axonIdentifier,
                                                                                                growthStep))));
    }
}
