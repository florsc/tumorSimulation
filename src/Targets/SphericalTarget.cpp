//
// Created by florian on 10/19/21.
//

#include "SphericalTarget.h"

SphericalTarget::SphericalTarget(const EuclideanVector &centerPoint, double radius)
        : m_centerPoint(centerPoint), m_radius(radius) {}

bool SphericalTarget::checkTargetReached(const EuclideanVector &position) {
    return (position - m_centerPoint).GetEuclideanNorm() < m_radius;
}
