//
// Created by florian on 9/13/21.
//

#include "HelperFunctions.h"
#include <cmath>
#include "EuclideanVector.h"
#include <iostream>

/*
EuclideanVector HelperFunctions::sph2cart(double az, double el, double r) {
    double rsin_theta = r * sin(el);
    double x = rsin_theta * cos(az);
    double y = rsin_theta * sin(az);
    double z = r * cos(el);
    return EuclideanVector(x, y, z);
}
*/

EuclideanVector HelperFunctions::sph2cart(double az, double el, double r) {
    double rsin_theta = r * cos(el);
    double x = rsin_theta * cos(az);
    double y = rsin_theta * sin(az);
    double z = r * sin(el);
    return EuclideanVector(x, y, z);
}

std::pair<double, double> HelperFunctions::getSphericalAngles(const EuclideanVector &v) {
    auto azimuth = atan2(v[1], v[0]);
    auto elevation = atan2(v[2], sqrt(v[0] * v[0] + v[1] * v[1]));
    return {2 * atan(azimuth), 2 * atan(elevation)};
}

bool
HelperFunctions::checkForDirectionSimilarity(const EuclideanVector &oldVector, const EuclideanVector &newVector,
                                             double threshold) {
    double tmp = std::acos(oldVector.CreateUnitVector() * newVector);
    return tmp < threshold;
}


std::vector<EuclideanVector>
HelperFunctions::createCoveringCenters(const EuclideanVector &start, const EuclideanVector &diff, double minDistance) {
    double centerDistance = minDistance;
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
