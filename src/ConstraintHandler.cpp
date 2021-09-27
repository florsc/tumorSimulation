//
// Created by florian on 9/9/21.
//

#include <memory>
#include <iostream>
#include "ConstraintHandler.h"

bool ConstraintHandler::checkForExteriorLimit(EuclideanVector position) {
    return m_exteriorLimit->checkExteriorLimitExceeded(position);
}

bool ConstraintHandler::checkForConstraint(std::vector<EuclideanVector> positions) {
    if (!checkForExteriorLimit(positions.back())) {
        return checkForOccupiedSpace(positions);
    }
    return true;
}

std::vector<std::vector<double>> createCenters(EuclideanVector start, EuclideanVector end);

bool ConstraintHandler::checkForOccupiedSpace(std::vector<EuclideanVector> positions) {
    if (!centerMap.empty()) {
        double low = std::min(positions.at(0).at(0), positions.back().at(0));
        double high = std::max(positions.at(0).at(0), positions.back().at(0));
        auto itLow = centerMap.lower_bound(low - distanceLimit);
        auto itHigh = centerMap.lower_bound(high + distanceLimit);
        bool collisionDetected = false;
        auto itLowTmp = itLow;
        while (itLowTmp != itHigh && !collisionDetected) {
            auto center = itLowTmp->second;
            for (const auto &position: positions) {
                if ((position - center) * (position - center) < distanceLimitSquared) {
                    collisionDetected = true;
                    break;
                }
            }
            itLowTmp++;
        }
        int positionIndex = 0;
        if (!collisionDetected) {
            while (itLow != itHigh) {
                while (positions.at(positionIndex).at(0) > itLow->first) {
                    positionIndex++;
                }
                centerMap.insert(std::make_pair(positions.at(positionIndex).at(0), positions.at(positionIndex)));
                itLow++;
            }
        }
        return collisionDetected;
    }
    return false;
}

ConstraintHandler::ConstraintHandler(std::shared_ptr<ExteriorLimit> exteriorLimit) : m_exteriorLimit(exteriorLimit) {

}

void ConstraintHandler::addConstraintCenters(std::vector<EuclideanVector> constraintCenters) {
    for (const auto &constraintCenter: constraintCenters) {
        centerMap.insert(std::make_pair(constraintCenter.at(0), constraintCenter));
    }
}
