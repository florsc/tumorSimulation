//
// Created by florian on 10/10/21.
//

#include "BaseAxon.h"
#include "../../util/EuclideanVector.h"
#include "../../Managers/SimulationManager.h"
#include "../../Managers/ConstraintManager.h"

BaseAxon::BaseAxon(EuclideanVector startPosition, int maxConstraintsEachGrowthStep,ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManagerHandle) : m_identifier(
        m_currentIdentifier), m_constraintHandler(
        constraintHandler), m_simulationManager(simulationManagerHandle), m_maxConstraintsEachGrowthStep(maxConstraintsEachGrowthStep) {
    m_tipPositions.push_back(startPosition);
    m_currentIdentifier++;
}

BaseAxon::BaseAxon(EuclideanVector startPosition, EuclideanVector nextPosition, int maxConstraintsEachGrowthStep,
                   ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManagerHandle) : m_identifier(
        m_currentIdentifier), m_constraintHandler(
        constraintHandler), m_simulationManager(simulationManagerHandle), m_maxConstraintsEachGrowthStep(maxConstraintsEachGrowthStep) {
    m_tipPositions.push_back(startPosition);
    m_tipPositions.push_back(nextPosition);
    m_currentIdentifier++;
}


int BaseAxon::m_currentIdentifier{0};

bool BaseAxon::isActive() const { return m_active; }

void BaseAxon::stopAxon() { m_active = false; }

PositionVector BaseAxon::getTipPositions() { return m_tipPositions; }

void BaseAxon::killAxon() {m_constraintHandler->freeSpace(m_identifier);
    if(auto simulationManager = m_simulationManager.lock()){
    simulationManager->removeAxon(m_identifier); m_isAlive = false; m_active = false;}}

bool BaseAxon::isAlive() const {
    return m_isAlive;
}
