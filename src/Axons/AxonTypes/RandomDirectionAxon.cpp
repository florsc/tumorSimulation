//
// Created by florian on 10/18/21.
//

#include "RandomDirectionAxon.h"
#include "../../SimulationSetUp/ParameterStruct.h"
#include "../../util/HelperFunctions.h"
#include "../../util/Samplers.h"
#include "../../Managers/SimulationManager.h"
#include "../../Managers/ConstraintManager.h"


RandomDirectionAxon::RandomDirectionAxon(int maxConstraintEncounters, double angleBackwardThreshold,
                                         SamplerHandle lengthSampler, EuclideanVector startPosition,
                                         ConstraintManagerHandle constraintManager,
                                         SimulationManagerHandle simulationManager)
        : BaseAxon(startPosition, maxConstraintEncounters, constraintManager, simulationManager),
          m_maxConstraintEncounters(maxConstraintEncounters), m_angleBackwardThreshold(angleBackwardThreshold),
          m_lengthSampler(lengthSampler) {
}

void RandomDirectionAxon::grow() {
    auto vec = sampleVector();
    if (m_tipPositions.size() > 1) {
        auto lastVector = m_tipPositions.back() - m_tipPositions.at(m_tipPositions.size() - 2);
        while (HelperFunctions::checkForDirectionSimilarity(-1 * lastVector, vec, m_angleBackwardThreshold)) {
            vec = sampleVector();
        }
    }
    vec = vec*m_lengthSampler->sample();
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), vec, parameters.minDistance);

    if (!m_constraintHandler->checkForConstraint(centers, m_identifier, m_tipPositions.size())) {
        m_tipPositions.emplace_back(m_tipPositions.back() + vec);

        if (checkBranching() && m_tipPositions.size() > 3) {
            createNewBranch();
        }
    } else {
        m_constraintCounter++;
        std::cout<<"a"<<std::endl;
        if (m_constraintCounter > m_maxConstraintEncounters) { stopAxon(); }
    }
}

bool RandomDirectionAxon::addPosition(EuclideanVector position) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          parameters.minDistance);
    if (m_constraintHandler->checkForConstraint(centers)) {
        m_tipPositions.push_back(position);
    } else {
        return false;
    }
    m_constraintHandler->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    return true;
}

EuclideanVector RandomDirectionAxon::sampleVector() {
    return EuclideanVector(m_normalDistribution(*m_generator), m_normalDistribution(*m_generator),
                           m_normalDistribution(*m_generator)).CreateUnitVector();
}

bool RandomDirectionAxon::checkBranching() {
    bool branch = std::bernoulli_distribution(parameters.branchingProbability)(*m_generator);
    return branch;
}

void RandomDirectionAxon::createNewBranch() {
    auto size = m_tipPositions.size();
    auto crossProductVector = crossProduct(m_tipPositions.at(size - 1) - m_tipPositions.at(size - 2),
                                           m_tipPositions.at(size - 2) - m_tipPositions.at(size - 3));
    if (auto simulationManager = m_simulationManager.lock()) {
        simulationManager->addStartedAxon(m_tipPositions.at(size - 1), m_tipPositions.at(size - 1)+(
                2*parameters.minDistance * crossProductVector.CreateUnitVector()));
    }
}
