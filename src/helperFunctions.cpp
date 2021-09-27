//
// Created by florian on 9/13/21.
//

#include "helperFunctions.h"
#include <cmath>
#include <iostream>

std::vector<double> HelperFunctions::sph2cart(double az, double el, double r) {
    double rsin_theta = r * sin(el);
    double x = rsin_theta * cos(az);
    double y = rsin_theta * sin(az);
    double z = r * cos(el);
    return std::vector<double>({x, y, z});
}

