//
// Created by florian on 9/13/21.
//

#ifndef TUMORSIMULATION_HELPERFUNCTIONS_H
#define TUMORSIMULATION_HELPERFUNCTIONS_H

#include <vector>
#include "EuclideanVector.h"

struct HelperFunctions {
    static std::vector<double> sph2cart(double az, double el, double r);

};


#endif //TUMORSIMULATION_HELPERFUNCTIONS_H
