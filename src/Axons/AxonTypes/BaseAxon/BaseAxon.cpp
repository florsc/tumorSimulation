//
// Created by florian on 10/10/21.
//

#include "BaseAxon.h"

#include <utility>
#include "../../../Managers/SimulationManager.h"
#include "../../../Managers/ConstraintManager.h"
#include "../../../Managers/TargetManager.h"
#include "../../../SimulationSetUp/ParameterStruct.h"
#include "../../../util/HelperFunctions.h"
#include "../../../util/simulationException.h"

BaseAxon::BaseAxon(const EuclideanVector &startPosition, BaseAxonParameters baseAxonParameters,
                   int constraintsEncountered)
        : m_identifier(
        m_currentIdentifier), m_baseAxonParameters(std::move(baseAxonParameters)), m_generator(parameters.m_generator),
          m_constraintCounter(constraintsEncountered) {
    m_tipPositions.push_back(startPosition);
    m_currentIdentifier++;
}

BaseAxon::BaseAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                   BaseAxonParameters baseAxonParameters, int constraintsEncountered)
        : m_identifier(
        m_currentIdentifier), m_baseAxonParameters(std::move(baseAxonParameters)), m_generator(parameters.m_generator),
          m_constraintCounter(constraintsEncountered) {
    m_tipPositions.push_back(startPosition);
    m_tipPositions.push_back(nextPosition);
    m_currentIdentifier++;
}


int BaseAxon::m_currentIdentifier{0};

void BaseAxon::killAxon() {
    if(!m_isAlive){throw simulationException("Can not kill axon twice.");}
    m_baseAxonParameters.constraintManager->freeSpace(m_identifier);
    if (auto simulationManager = m_baseAxonParameters.simulationManager.lock()) {
        simulationManager->removeAxon(m_identifier);
        m_isAlive = false;
        stopAxon();
    }
    for (const auto &childAxon: m_childAxons) {
        childAxon->killAxon();
    }
}

bool BaseAxon::checkTargetReached(const EuclideanVector &position) {
    if (m_baseAxonParameters.targetManager->checkTargetReached(position)) {
        m_targetReached = true;
        stopAxon();
        if (auto rootAxon = m_rootAxon.lock()) { rootAxon->setTargetReached(); }
    }
}

void BaseAxon::setTargetReached() {
    if(m_targetReached){throw simulationException("Can not reach target twice.");}
    m_targetReached = true;
    stopAxon();
    for (const auto &childAxon: m_childAxons) { childAxon->setTargetReached(); }
}

bool BaseAxon::checkConstraints(const PositionVector &positions) {
    return m_baseAxonParameters.constraintManager->checkForConstraint(positions);
}

bool BaseAxon::checkAxonGrowth(const PositionVector &positions) {
    if (checkConstraints(positions)) {
        m_constraintCounter++;
        if (checkConstraintEncounterLimit()) {
            stopAxon();
        }
        return true;
    }
    return false;
}

bool BaseAxon::checkConstraintEncounterLimit() {
    return m_constraintCounter > m_baseAxonParameters.maxNumberOfConstraintEncounters;
}

bool BaseAxon::createBranchIfPossible(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) {
    if (!checkConstraints(HelperFunctions::createCoveringCenters(startPosition, nextPosition - startPosition,
                                                                 parameters.minDistance))) {
        if (auto simulationManager = m_baseAxonParameters.simulationManager.lock()) {
            simulationManager->addStartedAxon(startPosition, nextPosition, m_constraintCounter, m_rootAxon);
            return true;
        }
    }
    return false;
}

bool BaseAxon::checkIfBranching() {
    bool branch = std::bernoulli_distribution(m_baseAxonParameters.branchingProbability)(*m_generator);
    return branch;
}

void BaseAxon::checkStopCondition() {
        if (m_constraintCounter > m_baseAxonParameters.maxNumberOfConstraintEncounters) { stopAxon(); }
    }
