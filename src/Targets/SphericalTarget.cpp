//
// Created by florian on 10/19/21.
//

#include "SphericalTarget.h"

SphericalTarget::SphericalTarget(const EuclideanVector &centerPoint, double radius, double gravityConstant)
        : m_centerPoint(centerPoint), m_radius(radius),m_gravityConstant(gravityConstant), m_mass(radius*radius*radius*M_PI) {}

bool SphericalTarget::checkTargetReached(const EuclideanVector &position) {
    return (position - m_centerPoint).GetEuclideanNorm() < m_radius;
}

EuclideanVector SphericalTarget::calculateForce(const EuclideanVector &position) {
    auto direction = m_centerPoint-position;
    return  m_gravityConstant * m_mass* direction/(direction*direction);
}
