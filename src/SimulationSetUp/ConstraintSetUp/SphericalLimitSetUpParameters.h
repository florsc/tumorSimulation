//
// Created by florian on 1/14/22.
//

#ifndef TUMORSIMULATION_SPHERICALTARGETSETUPPARAMETERS_H
#define TUMORSIMULATION_SPHERICALLIMITSETUPPARAMETERS_H


#include "ExteriorLimitSetUpParameters.h"

struct SphericalLimitSetUpParameters: public ExteriorLimitSetUpParameters {
double radius = 400;
};


#endif //TUMORSIMULATION_SPHERICALTARGETSETUPPARAMETERS_H
