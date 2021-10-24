//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_TARGET_H
#define TUMORSIMULATION_TARGET_H


#include "../util/EuclideanVector.h"

class Target {
public:
    virtual bool checkTargetReached(const EuclideanVector &position) = 0;
};


#endif //TUMORSIMULATION_TARGET_H
