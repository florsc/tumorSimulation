//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_CONSTRAINTHANDLER_H
#define TUMORSIMULATION_CONSTRAINTHANDLER_H


#include <vector>
#include <map>
#include "ExteriorLimit.h"
#include "EuclideanVector.h"

class ConstraintHandler {
    std::multimap<double, EuclideanVector> centerMap;
    std::shared_ptr<ExteriorLimit> m_exteriorLimit;
    double distanceLimitSquared{0.01};
    double distanceLimit{0.1};
public:
    ConstraintHandler(std::shared_ptr<ExteriorLimit> exteriorLimit);

    void addConstraintCenters(std::vector<EuclideanVector> constraintCenters);

    bool checkForConstraint(std::vector<EuclideanVector> positions);

    bool checkForOccupiedSpace(std::vector<EuclideanVector> position);

    bool checkForExteriorLimit(EuclideanVector position);
};


#endif //TUMORSIMULATION_CONSTRAINTHANDLER_H
