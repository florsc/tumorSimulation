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
#include "../../../util/SimulationException.h"

BaseAxon::BaseAxon(const EuclideanVector &startPosition, int id, BaseAxonParameters baseAxonParameters,
                   int constraintsEncountered)
        : m_identifier(id), m_baseAxonParameters(std::move(baseAxonParameters)), m_generator(parameters.m_generator),
          m_constraintCounter(constraintsEncountered) {
    m_tipPositions.push_back(startPosition);
}

BaseAxon::BaseAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition, int id,
                   BaseAxonParameters baseAxonParameters, int constraintsEncountered)
        : m_identifier(
        id), m_baseAxonParameters(std::move(baseAxonParameters)), m_generator(parameters.m_generator),
          m_constraintCounter(constraintsEncountered) {
    m_tipPositions.push_back(startPosition);
    m_tipPositions.push_back(nextPosition);
}

bool BaseAxon::checkConstraints(const PositionVector &positions)  const{
    return false;//m_baseAxonParameters.constraintManager->checkForConstraint(positions);
}

bool BaseAxon::checkIfBranching()  const{
    bool branch = std::bernoulli_distribution(m_baseAxonParameters.branchingProbability)(*m_generator);
    return branch;
}

bool BaseAxon::createBranchIfPossible(const EuclideanVector &startPosition, const EuclideanVector &nextPosition)  {

    if(m_numberOfBranches<ParameterStruct::maxNumberOfBranches){
    if (!checkConstraints(HelperFunctions::createCoveringCenters(startPosition, nextPosition - startPosition,
                                                                 ParameterStruct::minDistance))) {
        if (auto simulationManager = m_baseAxonParameters.simulationManager.lock()) {
            m_childAxons.push_back(simulationManager->addStartedAxon(startPosition, nextPosition, m_constraintCounter, m_rootAxon));
            increaseBranchNumberBase();
            m_childAxons.back()->setBranchNumber(m_numberOfBranches);
            return true;
        }
    }}
    return false;
}

void BaseAxon::checkForStopping() {
    if (m_constraintCounter > m_baseAxonParameters.maxNumberOfConstraintEncounters ) { stopAxon(); }
}

void BaseAxon::checkLength(){
    if(getAxonLength() > ParameterStruct::maxAxonLength){stopAxon();}
}

bool BaseAxon::checkTargetReached(const EuclideanVector &position) {
    if (m_baseAxonParameters.targetManager->checkTargetReached(position)) {
        if (auto rootAxon = m_rootAxon.lock()) { rootAxon->setTargetReached(); }
    }
}

void BaseAxon::setTargetReached() {
    if (m_targetReached) { throw SimulationException("Can not reach target twice."); }
    m_targetReached = true;
    stopAxonBranch();
    for (const auto &childAxon: m_childAxons) { childAxon->setTargetReached(); }
}

void BaseAxon::killAxon() {
    if (!m_isAlive) { throw SimulationException("Can not kill axon twice."); }
    m_baseAxonParameters.constraintManager->freeSpace(m_identifier);
    if (auto simulationManager = m_baseAxonParameters.simulationManager.lock()) {
        simulationManager->removeAxon(m_identifier);
        m_isAlive = false;
        stopAxonBranch();
    }
    for (const auto &childAxon: m_childAxons) {
        childAxon->killAxon();
    }
}

void BaseAxon::stopAxonBranch() { m_active = false;
    for(const auto& child:m_childAxons){child->stopAxonBranch();}}

void BaseAxon::stopAxon() { if(auto rootAxon = m_rootAxon.lock()){rootAxon->stopAxonBranch();}}
double BaseAxon::getAxonLength() {
    if(auto rootAxon = m_rootAxon.lock()){return rootAxon->getBranchLength();} return 0;
}

double BaseAxon::getBranchLength() {
    /*double length = 0;
    for(int i = 1;i<m_tipPositions.size();i++){
        length +=(m_tipPositions[i]-m_tipPositions[i-1]).GetEuclideanNorm();
    }
    for(const auto& childAxon: m_childAxons){
        length+=childAxon->getBranchLength();
    }*/
    return m_length;
}