//
// Created by florian on 9/9/21.
//

#include <memory>
#include "ConstraintManager.h"
#include <algorithm>
#include <utility>
#include <values.h>
#include "../ExteriorLimits/ExteriorLimit.h"
#include "../SimulationSetUp/ParameterStruct.h"

ConstraintManager::ConstraintManager() : m_exteriorLimit(parameters.exteriorLimit),
                                         m_distanceLimit(ParameterStruct::minDistance) {

}

ConstraintManager::ConstraintManager(std::shared_ptr<ExteriorLimit> exteriorLimit, double distanceLimit)
        : m_exteriorLimit(std::move(exteriorLimit)), m_distanceLimit(distanceLimit) {

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
                it--;
            }
        }

        m_centerMap.insert(it,
                           std::make_pair(itPos->at(0), ConstraintData(
                                   *itPos, axonIdentifier, growthStep)));
        itPos++;
    }
}

void ConstraintManager::freeSpace(int axonIdentifier, std::initializer_list<int> growthSteps) {

    for (auto it = m_centerMap.begin(); it != m_centerMap.end(); it++) {
        if (it->second.m_axonId == axonIdentifier) {
            if (std::find(growthSteps.begin(), growthSteps.end(), it->second.m_growthStep) != growthSteps.end()) {
                m_centerMap.erase(it);
            }
        }
    }
}

void ConstraintManager::freeSpace(int axonIdentifier) {
    for (auto it = m_centerMap.begin(); it != m_centerMap.end(); it++) {
        if (it->second.m_axonId == axonIdentifier) {
            m_centerMap.erase(it);
        }
    }
}

bool ConstraintManager::checkForConstraint(const std::vector<EuclideanVector> &positions, int axonIdentifier,
                                           int growthStep) {
    if(!checkForConstraint(positions)){
        addConstraintCenters(positions,axonIdentifier,growthStep);
        return false;
    }
    return true;
}

bool ConstraintManager::checkForConstraint(const std::vector<EuclideanVector> &positions) const{
    if(positions.empty()){return true;}
    if (!checkForExteriorLimit(positions.back())) {
        return checkForOccupiedSpace(positions);
    }
    return true;
}

bool ConstraintManager::checkForOccupiedSpace(const std::vector<EuclideanVector> &positions)  const{
    if (!m_centerMap.empty()) {
        double maxSquaredDistanceToBegin = 0;
        double low = MAXFLOAT;
        double high = MINFLOAT;
        EuclideanVector tmpDiffVector;

        for (const auto &position: positions) {
            tmpDiffVector = position - positions[0];
            auto distSquared = (tmpDiffVector) * (tmpDiffVector);
            if (distSquared > maxSquaredDistanceToBegin) { maxSquaredDistanceToBegin = distSquared; }
            low = std::min(position[0], low);
            high = std::max(position[0], high);
        }
        auto itLow = m_centerMap.lower_bound(low - m_distanceLimit);
        auto itHigh = m_centerMap.upper_bound(high + m_distanceLimit);
        auto itLowTmp = itLow;
        double distanceLimitSquared = m_distanceLimit * m_distanceLimit;
        while (itLowTmp != itHigh) {

            auto center = itLowTmp->second.m_position;
            if ((positions[0] - center) * (positions[0] - center) < maxSquaredDistanceToBegin + distanceLimitSquared) {
                for (const auto &position: positions) {
                    tmpDiffVector = position - center;
                    if (tmpDiffVector * tmpDiffVector < distanceLimitSquared) {
                        return true;
                    }
                }
            }
            itLowTmp++;
        }
}
return false;}

bool ConstraintManager::checkForExteriorLimit(const EuclideanVector &position)  const{
    return m_exteriorLimit->checkExteriorLimitExceeded(position);
}
