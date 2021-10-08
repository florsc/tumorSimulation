//
// Created by florian on 9/9/21.
//

#include <memory>
#include <iostream>
#include "ConstraintHandler.h"

bool ConstraintHandler::checkForExteriorLimit(const EuclideanVector& position) {
    return m_exteriorLimit->checkExteriorLimitExceeded(position);
}

bool ConstraintHandler::checkForConstraint(const std::vector<EuclideanVector>& positions) {
    if (!checkForExteriorLimit(positions.back())) {
        return checkForOccupiedSpace(positions);
    }
    return true;
}

bool ConstraintHandler::checkForOccupiedSpace(const std::vector<EuclideanVector>& positions) {
    if (!m_centerMap.empty()) {
        double low = std::min(positions.at(0).at(0), positions.back().at(0));
        double high = std::max(positions.at(0).at(0), positions.back().at(0));
        auto itLow = m_centerMap.lower_bound(low - m_distanceLimit);
        auto itHigh = m_centerMap.lower_bound(high + m_distanceLimit);
        auto itLowTmp = itLow;
        double distanceLimitSquared = m_distanceLimit * m_distanceLimit;
        while (itLowTmp != itHigh) {
            auto center = itLowTmp->second;
            for (const auto &position: positions) {
                if ((position - center) * (position - center) < distanceLimitSquared) {
                    return true;
                }
            }
            itLowTmp++;
        }
        auto itPos = positions.begin();
        while(itPos != positions.end()){
            while(itLow != itHigh && itLow->first<itPos->at(0)){
                itLow++;}

        m_centerMap.insert(std::make_pair(itPos->at(0), *itPos));
        itPos++;
        }
    }
    else{ addConstraintCenters(positions);}
    return false;
}

ConstraintHandler::ConstraintHandler() : m_exteriorLimit(std::move(parameters.exteriorLimit)), m_distanceLimit(parameters.minDistance) {

}

ConstraintHandler::ConstraintHandler(std::shared_ptr<ExteriorLimit>&& exteriorLimit, double distanceLimit):m_exteriorLimit(std::move(exteriorLimit)),m_distanceLimit(distanceLimit){

}

void ConstraintHandler::addConstraintCenters(const std::vector<EuclideanVector>& constraintCenters) {
    for (const auto &constraintCenter: constraintCenters) {
        m_centerMap.insert(std::make_pair(constraintCenter.at(0), constraintCenter));
    }
}
