//
// Created by florian on 1/17/22.
//

#ifndef TUMORSIMULATION_SPHERICALTARGETSETUPPARAMETERS_H
#define TUMORSIMULATION_SPHERICALTARGETSETUPPARAMETERS_H


#include "../../util/EuclideanVector.h"
#include "TargetSetUpParameters.h"

struct SphericalTargetSetUpParameters :public TargetSetUpParameters{
    EuclideanVector centerPoint;
    double radius;
    double gravityConstant;
};


#endif //TUMORSIMULATION_SPHERICALTARGETSETUPPARAMETERS_H
