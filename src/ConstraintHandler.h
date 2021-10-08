//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_CONSTRAINTHANDLER_H
#define TUMORSIMULATION_CONSTRAINTHANDLER_H

#include <iostream>
#include <vector>
#include <map>
#include "ExteriorLimit.h"
#include "EuclideanVector.h"
#include "ParameterStruct.h"

class ConstraintHandler {
    std::multimap<double, std::pair<EuclideanVector, std::pair<int, int>>> m_centerMap;
    std::shared_ptr<ExteriorLimit> m_exteriorLimit;
    double m_distanceLimit;

public:
    ConstraintHandler();

    explicit ConstraintHandler(std::shared_ptr<ExteriorLimit>&& exteriorLimit, double distanceLimit);

    void addConstraintCenters(const std::vector<EuclideanVector>& constraintCenters, int axonIdentifier=0, int growthStep=0);

    void freeSpace(int axonIdentifier, std::initializer_list<int> growthSteps);

    bool checkForConstraint(const std::vector<EuclideanVector>& positions, int axonIdentifier=0, int growthStep=0);

    bool checkForOccupiedSpace(const std::vector<EuclideanVector>& position, int axonIdentifier=0, int growthStep=0);

    bool checkForExteriorLimit(const EuclideanVector& position);

    ~ConstraintHandler(){std::cout<<"ConstraintHandler destructed"<<std::endl;}

};


#endif //TUMORSIMULATION_CONSTRAINTHANDLER_H
