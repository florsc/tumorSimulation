//
// Created by florian on 9/13/21.
//

#include "helperFunctions.h"
#include <cmath>
#include <iostream>

std::vector<double> HelperFunctions::sph2cart(double az, double el, double r) {
    double rsin_theta = r * sin(el);
    double x = rsin_theta * cos(az);
    double y = rsin_theta * sin(az);
    double z = r * cos(el);
    return std::vector<double>({x, y, z});
}

std::vector<EuclideanVector> HelperFunctions::sampleStartPositions(EuclideanVector c1, EuclideanVector c2) {
    double minDistance = 0.1;
    auto diff = c2 - c1;
    std::vector<std::vector<double>> spacedAxisValues;
    for (int i = 0; i < 3; i++) {
        spacedAxisValues.emplace_back();
        if (diff.at(i) <= minDistance) {
            spacedAxisValues.at(i).push_back(c1.at(i) + diff.at(i) / 2);
        } else {
            int numberOfPositions = ceil(diff.at(i) / minDistance);
            double equalSpace = diff.at(i) / (numberOfPositions - 1);
            for (int j = 0; j < numberOfPositions; j++) {
                spacedAxisValues.at(i).push_back(c1.at(i) + j * equalSpace);
            }
        }
    }
    std::vector<EuclideanVector> startPositions;
    for (const auto &xValue: spacedAxisValues.at(0)) {
        for (const auto &yValue: spacedAxisValues.at(1)) {
            for (const auto &zValue: spacedAxisValues.at(2)) {
                startPositions.push_back(EuclideanVector({xValue, yValue, zValue}));
            }
        }
    }
    return startPositions;
}
