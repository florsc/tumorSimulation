//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_CONSTRAINTMANAGER_H
#define TUMORSIMULATION_CONSTRAINTMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "../util/EuclideanVector.h"
#include "../SimulationSetUp/ParameterStruct.h"

class ExteriorLimit;
struct ConstraintData{
    EuclideanVector m_position;
    int m_axonId;
    int m_growthStep;
    ConstraintData(const EuclideanVector& position, int axonId, int growthStep):m_position(position),m_axonId(axonId),m_growthStep(growthStep){}

    bool operator==(const ConstraintData& constraintData) const {return m_position == constraintData.m_position &&m_growthStep == constraintData.m_growthStep && m_axonId==constraintData.m_axonId;};
};
class ConstraintManager {
    std::multimap<double, ConstraintData> m_centerMap;
    std::shared_ptr<ExteriorLimit> m_exteriorLimit;
    double m_distanceLimit;

public:
    bool checkForConstraint(const EuclideanVector& start, const EuclideanVector& growthVector) const;

    ConstraintManager(ParameterStruct& modelParameters);

    ConstraintManager(ParameterStruct& modelParameters, std::shared_ptr<ExteriorLimit> exteriorLimit);

    void addAxons(const std::vector<EuclideanVector> &growthPoints, int axonIdentifier,
                                     int growthStep);
    virtual void addConstraintCenters(const std::vector<EuclideanVector> &constraintCenters, int axonIdentifier = 0,
                              int growthStep = 0);

    void freeSpace(int axonIdentifier, std::initializer_list<int> growthSteps);

    void freeSpace(int axonIdentifier);

    bool checkForConstraintAndAdd(const EuclideanVector& start, const EuclideanVector& growthVector, int axonIdentifier, int growthStep);

    bool checkForConstraintAndAdd(const std::vector<EuclideanVector> &positions, int axonIdentifier, int growthStep);

    [[nodiscard]] virtual bool checkForConstraint(const std::vector<EuclideanVector> &positions) const;

    bool operator==(const ConstraintManager& constraintManager) const {return m_centerMap == constraintManager.m_centerMap && m_distanceLimit == constraintManager.m_distanceLimit && m_exteriorLimit==constraintManager.m_exteriorLimit;};

private:
    [[nodiscard]] bool checkForOccupiedSpace(const std::vector<EuclideanVector> &position) const;

    [[nodiscard]] bool checkForExteriorLimit(const EuclideanVector &position) const;

};


#endif //TUMORSIMULATION_CONSTRAINTMANAGER_H
