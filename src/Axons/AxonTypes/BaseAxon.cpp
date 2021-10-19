//
// Created by florian on 10/10/21.
//

#include "BaseAxon.h"
#include "../../Managers/SimulationManager.h"
#include "../../Managers/ConstraintManager.h"
#include "../../SimulationSetUp/ParameterStruct.h"

BaseAxon::BaseAxon(const EuclideanVector& startPosition, int maxConstraintsEachGrowthStep,
                   ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManagerHandle)
        : m_identifier(
        m_currentIdentifier), m_constraintHandler(std::move(
        constraintHandler)), m_simulationManager(std::move(simulationManagerHandle)),
          m_maxConstraintsEachGrowthStep(maxConstraintsEachGrowthStep), m_generator(parameters.m_generator) {
    m_tipPositions.push_back(startPosition);
    m_currentIdentifier++;
}

BaseAxon::BaseAxon(const EuclideanVector& startPosition, const EuclideanVector& nextPosition, int maxConstraintsEachGrowthStep,
                   ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManagerHandle)
        : m_identifier(
        m_currentIdentifier), m_constraintHandler(std::move(
        constraintHandler)), m_simulationManager(std::move(simulationManagerHandle)),
          m_maxConstraintsEachGrowthStep(maxConstraintsEachGrowthStep), m_generator(parameters.m_generator) {
    m_tipPositions.push_back(startPosition);
    m_tipPositions.push_back(nextPosition);
    m_currentIdentifier++;
}


int BaseAxon::m_currentIdentifier{0};

void BaseAxon::killAxon() {
    m_constraintHandler->freeSpace(m_identifier);
    if (auto simulationManager = m_simulationManager.lock()) {
        simulationManager->removeAxon(m_identifier);
        m_isAlive = false;
        stopAxon();
    }
}

