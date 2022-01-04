//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_SPHERICALTARGET_H
#define TUMORSIMULATION_SPHERICALTARGET_H


#include "Target.h"

class SphericalTarget : public Target {
    EuclideanVector m_centerPoint;
    double m_radius;
    double m_gravityConstant;
public:
    SphericalTarget(const EuclideanVector &centerPoint, double radius, double gravityConstant=0);

    EuclideanVector calculateForce(const EuclideanVector& position) override;
    bool checkTargetReached(const EuclideanVector &position) override;

    double m_mass;
};


#endif //TUMORSIMULATION_SPHERICALTARGET_H
