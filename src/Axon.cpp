//
// Created by florian on 9/9/21.
//

#include <iostream>
#include "Axon.h"
#include "helperFunctions.h"

Axon::Axon() {}

double Axon::angleDifferenceCalculator(double a1, double a2) {
    return std::min(std::abs(a1 - a2), 2 * M_PI - std::abs(a1 - a2));
}

bool Axon::checkForBackwardGrowth(double previousAz, double previousEl, double newAz, double newEl, double threshold) {
    double tmp = M_PI - std::acos(cos(previousEl) * cos(newEl) + sin(previousEl) * cos(previousAz) * sin(newEl) * cos(newAz) +
                           sin(previousEl) * sin(previousAz) * sin(newEl) * sin(newAz));
    return tmp < threshold;
}

void Axon::growthStep(double i) {
    double az = azSampler(generator);
    double el = elSampler(generator);
    int j = 0;
    if (!angles.empty()) {
        while (checkForBackwardGrowth(az, el, angles.back().at(0), angles.back().at(1), 0.9 * M_PI)) {
            az = azSampler(generator);
            el = elSampler(generator);
        }
    }
    angles.push_back({az, el});
    std::vector<double> cartesianGrowthVector = HelperFunctions::sph2cart(az, el, 1);

    if (!tipPositions.empty()) {
        tipPositions.push_back(std::vector<double>({tipPositions.back().at(0) + cartesianGrowthVector.at(0),
                                                    tipPositions.back().at(1) + cartesianGrowthVector.at(1),
                                                    tipPositions.back().at(2) + cartesianGrowthVector.at(2)}));
    } else {
        tipPositions.push_back((cartesianGrowthVector));
    }
}

void Axon::run() {
    for (int i = 0; i < 100; i++) {
        growthStep(i);
    }

}
