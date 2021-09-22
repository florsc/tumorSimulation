//
// Created by florian on 9/17/21.
//

#include "ExteriorLimit.h"

SphericalLimit::SphericalLimit(double radius) : m_radiusSquared(radius * radius) {

}

bool SphericalLimit::checkExteriorLimitExceeded(EuclideanVector position) {
    return position.at(0) * position.at(0) + position.at(1) * position.at(1) + position.at(2) * position.at(2) >
           m_radiusSquared;
}
