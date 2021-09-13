//
// Created by florian on 9/9/21.
//
#include <memory>
#include <vector>
#include "OccupiedSpace.h"

#ifndef TUMORSIMULATION_AXON_H
#define TUMORSIMULATION_AXON_H


class Axon {
    using PositionList = std::vector<std::vector<double>>;
    PositionList tipPositions;
public:
    PositionList getTipPositions(){return tipPositions;}
    std::shared_ptr<OccupiedSpace> occupiedSpaceCenters;
    Axon();
    ~Axon(){};
    void growthStep(double i);
    void run();
};


#endif //TUMORSIMULATION_AXON_H
