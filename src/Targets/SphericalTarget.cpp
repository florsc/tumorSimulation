//
// Created by florian on 10/19/21.
//

#include "SphericalTarget.h"
#include "../SimulationSetUp/TargetSetUp/SphericalTargetSetUpParameters.h"

SphericalTarget::SphericalTarget(SphericalTargetSetUpParametersHandle sphericalTargetSetUpParameters)
        : m_centerPoint(sphericalTargetSetUpParameters->centerPoint), m_radius(sphericalTargetSetUpParameters->radius),
          m_gravityConstant(sphericalTargetSetUpParameters->gravityConstant),
          m_mass(sphericalTargetSetUpParameters->radius * sphericalTargetSetUpParameters->radius *
                 sphericalTargetSetUpParameters->radius * M_PI) {}

bool SphericalTarget::checkTargetReached(const EuclideanVector &position) {
    return (position - m_centerPoint).GetEuclideanNorm() < m_radius;
}

EuclideanVector SphericalTarget::calculateForce(const EuclideanVector &position) {
    auto direction = m_centerPoint - position;
    return m_gravityConstant * m_mass * direction / (direction * direction);
}
