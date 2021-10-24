//
// Created by florian on 9/9/21.
//

#include <memory>
#include <iostream>
#include "ConstraintManager.h"
#include <algorithm>
#include <values.h>
#include "../ExteriorLimits/ExteriorLimit.h"
#include "../SimulationSetUp/ParameterStruct.h"

ConstraintManager::ConstraintManager() : m_exteriorLimit(parameters.exteriorLimit),
                                         m_distanceLimit(parameters.minDistance) {

}

ConstraintManager::ConstraintManager(std::shared_ptr<ExteriorLimit> exteriorLimit, double distanceLimit)
        : m_exteriorLimit(exteriorLimit), m_distanceLimit(distanceLimit) {

}

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
        double maxSquaredDistanceToBegin = 0;
        double low = MAXFLOAT;
        double high = MINFLOAT;
        for (const auto &position: positions) {
            auto distSquared = (position - positions[0]) * (position - positions[0]);
            if (distSquared > maxSquaredDistanceToBegin) { maxSquaredDistanceToBegin = distSquared; }
            low = std::min(position[0], low);
            high = std::max(position[0], high);
        }
        auto itLow = m_centerMap.lower_bound(low - m_distanceLimit);
        auto itHigh = m_centerMap.upper_bound(high + m_distanceLimit);
        auto itLowTmp = itLow;
        double distanceLimitSquared = m_distanceLimit * m_distanceLimit;
        while (itLowTmp != itHigh) {

            auto center = itLowTmp->second.first;
            if ((positions[0] - center) * (positions[0] - center) < maxSquaredDistanceToBegin + distanceLimitSquared) {
                for (const auto &position: positions) {
                    if ((position - center) * (position - center) < distanceLimitSquared) {
                        return true;
                    }
                }
            }
            itLowTmp++;
        }
        if (addCenters) {
            auto it = itLow;
            auto itPos = positions.begin();
            while (itPos != positions.end()) {
                if (it->first < itPos->at(0)) {
                    while (it != itHigh && it->first < itPos->at(0)) {
                        it++;
                    }
                } else {
                    while (it != itLow && it->first > itPos->at(0)) {
                        itLow--;
                    }
                }
                m_centerMap.insert(it,
                                   std::make_pair(itPos->at(0),
                                                  std::make_pair(*itPos, std::make_pair(axonIdentifier, growthStep))));
                itPos++;
            }
        }
    } else { addConstraintCenters(positions); }
    return false;
}

void ConstraintManager::addConstraintCenters(const std::vector<EuclideanVector> &constraintCenters, int axonIdentifier,
                                             int growthStep) {

    double low = MAXFLOAT;
    double high = MINFLOAT;
    for (const auto &position: constraintCenters) {
        low = std::min(position[0], low);
        high = std::max(position[0], high);
    }
    auto itLow = m_centerMap.lower_bound(low - m_distanceLimit);
    auto itHigh = m_centerMap.upper_bound(high + m_distanceLimit);
    auto it = itLow;
    auto itPos = constraintCenters.begin();
    while (itPos != constraintCenters.end()) {
        if (it->first < itPos->at(0)) {
            while (it != itHigh && it->first < itPos->at(0)) {
                it++;
            }
        } else {
            while (it != itLow && it->first > itPos->at(0)) {
                itLow--;
            }
        }
        m_centerMap.insert(it,
                           std::make_pair(itPos->at(0),
                                          std::make_pair(*itPos, std::make_pair(axonIdentifier, growthStep))));
        itPos++;
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

void ConstraintManager::freeSpace(int axonIdentifier) {
    for (auto it = m_centerMap.begin(); it != m_centerMap.end(); it++) {
        if (it->second.second.first == axonIdentifier) {
            m_centerMap.erase(it);
        }
    }
}
