//
// Created by florian on 9/9/21.
//
#include <memory>
#include <vector>
#include "OccupiedSpace.h"

#ifndef TUMORSIMULATION_AXON_H
#define TUMORSIMULATION_AXON_H


class Axon {
    std::shared_ptr<OccupiedSpace> occupiedSpaceCenters;
    Axon();
    ~Axon();
};


#endif //TUMORSIMULATION_AXON_H
