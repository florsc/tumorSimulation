//
// Created by florian on 1/17/22.
//

#include "SphericalTargetSetUpParameters.h"
//spherical target for
SphericalTargetSetUpParameters::SphericalTargetSetUpParameters() : TargetSetUpParameters() {
    centerPoint = EuclideanVector(0, 0, 0);
    radius = 1;
    gravityConstant = 1; //regulates the strength of a pulling force from targets, currently turned off
};