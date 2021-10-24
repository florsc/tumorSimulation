//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_SPHERICALTARGET_H
#define TUMORSIMULATION_SPHERICALTARGET_H


#include "Target.h"

class SphericalTarget : public Target {
    EuclideanVector m_centerPoint;
    double m_radius;
public:
    [[maybe_unused]] SphericalTarget(const EuclideanVector &centerPoint, double radius);

    bool checkTargetReached(const EuclideanVector &position) override;
};


#endif //TUMORSIMULATION_SPHERICALTARGET_H
