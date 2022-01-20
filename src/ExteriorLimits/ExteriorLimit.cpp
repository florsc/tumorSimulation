//
// Created by florian on 9/17/21.
//

#include "ExteriorLimit.h"
#include "../SimulationSetUp/ConstraintSetUp/SphericalLimitSetUpParameters.h"

SphericalLimit::SphericalLimit(SphericalLimitSetUpParametersHandle sphericalLimitSetUpParameters) : m_radiusSquared(sphericalLimitSetUpParameters->radius * sphericalLimitSetUpParameters->radius) {

}

bool SphericalLimit::checkExteriorLimitExceeded(EuclideanVector position) const {
    return position.at(0) * position.at(0) + position.at(1) * position.at(1) + position.at(2) * position.at(2) >
           m_radiusSquared;
}
