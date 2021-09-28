//
// Created by florian on 9/9/21.
//

#include <iostream>
#include "Axon.h"
#include "helperFunctions.h"

Axon::Axon(int identifier, EuclideanVector startPosition, std::shared_ptr<ConstraintHandler> constraintHandler,
           std::shared_ptr<ProcessSampler> processSampler, AxonManager& axonManager) : m_identifier(identifier), m_constraintHandler(
        constraintHandler), m_processSampler(processSampler), m_AxonManager(axonManager) {
    tipPositions.push_back(startPosition);
}

Axon::Axon(int identifier, EuclideanVector startPosition, EuclideanVector nextPosition, std::shared_ptr<ConstraintHandler> constraintHandler,
           std::shared_ptr<ProcessSampler> processSampler, AxonManager& axonManager) : m_identifier(identifier), m_constraintHandler(
        constraintHandler), m_processSampler(processSampler), m_AxonManager(axonManager) {
    tipPositions.push_back(startPosition);
    tipPositions.push_back(nextPosition);
}

double Axon::angleDifferenceCalculator(double a1, double a2) {
    return std::min(std::abs(a1 - a2), 2 * M_PI - std::abs(a1 - a2));
}

std::vector<EuclideanVector> Axon::createCenters(EuclideanVector start, EuclideanVector diff) {
    double centerDistance = 0.1;
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

bool Axon::checkForBackwardGrowth(double previousAz, double previousEl, double newAz, double newEl, double threshold) {
    double tmp = M_PI -
                 std::acos(cos(previousEl) * cos(newEl) + sin(previousEl) * cos(previousAz) * sin(newEl) * cos(newAz) +
                           sin(previousEl) * sin(previousAz) * sin(newEl) * sin(newAz));
    return tmp < threshold;
}

std::shared_ptr<Axon> Axon::createNewBranch() {
    auto size = tipPositions.size();
    std::cout<<"a"<<std::endl;
    std::cout<<size<<std::endl;
    auto crossProductVector = crossProduct(tipPositions.at(size-1)-tipPositions.at(size-2),tipPositions.at(size-2)-tipPositions.at(size-3));
    std::cout<<"b"<<std::endl;
    return std::shared_ptr<Axon>(new Axon(m_AxonManager.getNumOfAxons(),tipPositions.at(size-2),tipPositions.at(size-2)+0.1*crossProductVector.CreateUnitVector(),m_constraintHandler,m_processSampler, m_AxonManager));
}

void Axon::growthStep() {
    double az = std::acos(1 - sampler(generator));
    double el = 2 * M_PI * sampler(generator);
    if (!angles.empty()) {
        while (checkForBackwardGrowth(az, el, angles.back().at(0), angles.back().at(1), 0.3 * M_PI)) {
            az = std::acos(1 - sampler(generator));
            el = 2 * M_PI * sampler(generator);
        }
    }
    angles.push_back({az, el});
    std::vector<double> cartesianGrowthVectorTmp = HelperFunctions::sph2cart(az, el, m_processSampler->sampleLength());
    EuclideanVector cartesianGrowthVector(cartesianGrowthVectorTmp.begin(), cartesianGrowthVectorTmp.end());
    auto centers = createCenters(tipPositions.back(), cartesianGrowthVector);
    if (!m_constraintHandler->checkForConstraint(centers)) {
        tipPositions.emplace_back(tipPositions.back() + cartesianGrowthVector);
    }
    if(m_processSampler->branch()&& tipPositions.size()>4){
        m_AxonManager.addAxon(createNewBranch());

    }
}

