//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_OCCUPIEDSPACE_H
#define TUMORSIMULATION_OCCUPIEDSPACE_H


#include <vector>

class OccupiedSpace {
    std::vector<double[3]> occupiedSpaceCenters;
    bool checkForOccupiedSpace(const double*);
};


#endif //TUMORSIMULATION_OCCUPIEDSPACE_H
