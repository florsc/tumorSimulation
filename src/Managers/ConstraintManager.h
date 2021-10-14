//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_CONSTRAINTMANAGER_H
#define TUMORSIMULATION_CONSTRAINTMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "../ExteriorLimits/ExteriorLimit.h"
#include "../util/EuclideanVector.h"
#include "../SimulationSetUp/ParameterStruct.h"

class ConstraintManager {
    std::multimap<double, std::pair<EuclideanVector, std::pair<int, int>>> m_centerMap;
    std::shared_ptr<ExteriorLimit> m_exteriorLimit;
    double m_distanceLimit;

public:
    ConstraintManager();

    explicit ConstraintManager(std::shared_ptr<ExteriorLimit> &&exteriorLimit, double distanceLimit);

    void addConstraintCenters(const std::vector<EuclideanVector> &constraintCenters, int axonIdentifier = 0,
                              int growthStep = 0);

    void addConstraintCenters(const std::list<EuclideanVector> &constraintCenters, int axonIdentifier = 0,
                              int growthStep = 0);

    void freeSpace(int axonIdentifier, std::initializer_list<int> growthSteps);

    bool checkForConstraint(const std::vector<EuclideanVector> &positions, int axonIdentifier, int growthStep);

    bool checkForConstraint(const std::vector<EuclideanVector> &positions);

    ~ConstraintManager() { std::cout << "ConstraintManager destructed" << std::endl; }

private:
    bool checkForOccupiedSpace(const std::vector<EuclideanVector> &position, int axonIdentifier, int growthStep,
                               bool addCenters);

    bool checkForExteriorLimit(const EuclideanVector &position);

};


#endif //TUMORSIMULATION_CONSTRAINTMANAGER_H
