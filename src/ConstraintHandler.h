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
    std::multimap<double, EuclideanVector> m_centerMap;
    std::shared_ptr<ExteriorLimit> m_exteriorLimit;
    double m_distanceLimit;
public:
    ConstraintHandler();

    explicit ConstraintHandler(std::shared_ptr<ExteriorLimit>&& exteriorLimit, double distanceLimit);

    void addConstraintCenters(const std::vector<EuclideanVector>& constraintCenters);

    bool checkForConstraint(const std::vector<EuclideanVector>& positions);

    bool checkForOccupiedSpace(const std::vector<EuclideanVector>& position);

    bool checkForExteriorLimit(const EuclideanVector& position);

    ~ConstraintHandler(){std::cout<<"ConstraintHandler destructed"<<std::endl;}

};


#endif //TUMORSIMULATION_CONSTRAINTHANDLER_H
