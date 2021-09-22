//
// Created by florian on 9/9/21.
//

#include <iostream>
#include "Axon.h"
#include "helperFunctions.h"

Axon::Axon(EuclideanVector startPosition, std::shared_ptr<ConstraintHandler> constraintHandler) : m_constraintHandler(
        constraintHandler) {
    tipPositions.push_back(startPosition);
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
    return std::vector<EuclideanVector>();
}

bool Axon::checkForBackwardGrowth(double previousAz, double previousEl, double newAz, double newEl, double threshold) {
    double tmp = M_PI -
                 std::acos(cos(previousEl) * cos(newEl) + sin(previousEl) * cos(previousAz) * sin(newEl) * cos(newAz) +
                           sin(previousEl) * sin(previousAz) * sin(newEl) * sin(newAz));
    return tmp < threshold;
}

void Axon::growthStep(double i) {
    double az = azSampler(generator);
    double el = elSampler(generator);
    if (!angles.empty()) {
        while (checkForBackwardGrowth(az, el, angles.back().at(0), angles.back().at(1), 0.9 * M_PI)) {
            az = azSampler(generator);
            el = elSampler(generator);
        }
    }
    angles.push_back({az, el});
    std::vector<double> cartesianGrowthVectorTmp = HelperFunctions::sph2cart(az, el, 1);
    EuclideanVector cartesianGrowthVector(cartesianGrowthVectorTmp.begin(), cartesianGrowthVectorTmp.end());
    auto centers = createCenters(tipPositions.back(), cartesianGrowthVector);
    if (!m_constraintHandler->checkForConstraint(centers)) {
        tipPositions.emplace_back(tipPositions.back() + cartesianGrowthVector);
    }
}

void Axon::run() {
    for (int i = 0; i < 100; i++) {
        growthStep(i);
    }

}
