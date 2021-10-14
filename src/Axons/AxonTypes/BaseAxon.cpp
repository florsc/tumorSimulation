//
// Created by florian on 10/10/21.
//

#include "BaseAxon.h"
#include "../../util/EuclideanVector.h"

BaseAxon::BaseAxon(EuclideanVector startPosition, std::shared_ptr<ConstraintManager> constraintHandler) : m_identifier(
        m_currentIdentifier), m_constraintHandler(
        constraintHandler) {
    m_tipPositions.push_back(startPosition);
    m_currentIdentifier++;
}

BaseAxon::BaseAxon(EuclideanVector startPosition, EuclideanVector nextPosition,
                   std::shared_ptr<ConstraintManager> constraintHandler) : m_identifier(
        m_currentIdentifier), m_constraintHandler(
        constraintHandler) {
    m_tipPositions.push_back(startPosition);
    m_tipPositions.push_back(nextPosition);
    m_currentIdentifier++;
}


int BaseAxon::m_currentIdentifier{0};

bool BaseAxon::isActive() const { return m_active; }

void BaseAxon::stopAxon() { m_active = false; }

PositionVector BaseAxon::getTipPositions() { return m_tipPositions; }
