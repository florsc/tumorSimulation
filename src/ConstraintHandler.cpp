//
// Created by florian on 9/9/21.
//

#include <memory>
#include <iostream>
#include "ConstraintHandler.h"
#include <algorithm>

bool ConstraintHandler::checkForExteriorLimit(const EuclideanVector& position) {
    return m_exteriorLimit->checkExteriorLimitExceeded(position);
}

bool ConstraintHandler::checkForConstraint(const std::vector<EuclideanVector>& positions, int axonIdentifier, int growthStep) {
    if (!checkForExteriorLimit(positions.back())) {
        return checkForOccupiedSpace(positions, axonIdentifier, growthStep);
    }
    return true;
}

bool ConstraintHandler::checkForOccupiedSpace(const std::vector<EuclideanVector>& positions, int axonIdentifier, int growthStep) {
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
        auto itPos = positions.begin();
        while(itPos != positions.end()){
            while(itLow != itHigh && itLow->first<itPos->at(0)){
                itLow++;}

        m_centerMap.insert(std::make_pair(itPos->at(0), std::make_pair(*itPos,std::make_pair(axonIdentifier,growthStep))));
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

void ConstraintHandler::addConstraintCenters(const std::vector<EuclideanVector>& constraintCenters, int axonIdentifier, int growthStep) {
    for (const auto &constraintCenter: constraintCenters) {
        m_centerMap.insert(std::make_pair(constraintCenter.at(0), std::make_pair(constraintCenter,std::make_pair(axonIdentifier,growthStep))));
    }
}

void ConstraintHandler::freeSpace(int axonIdentifier, std::initializer_list<int> growthSteps) {

    for(auto it = m_centerMap.begin();it!=m_centerMap.end();it++){
        if(it->second.second.first == axonIdentifier){
            if(std::find(growthSteps.begin(), growthSteps.end(), it->second.second.second)!=growthSteps.end()){
                m_centerMap.erase(it);
            }
        }
    }
}
