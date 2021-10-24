//
// Created by florian on 10/18/21.
//

#include "RandomDirectionAxon.h"
#include "../../../SimulationSetUp/ParameterStruct.h"
#include "../../../util/HelperFunctions.h"
#include "../../../util/Samplers.h"
#include "../../../Managers/SimulationManager.h"
#include "../../../Managers/ConstraintManager.h"


RandomDirectionAxon::RandomDirectionAxon(EuclideanVector startPosition,
                                         RandomDirectionAxonParameters randomDirectionAxonParameters,
                                         BaseAxonParameters baseAxonParameters, int constraintsEncountered)
        : BaseAxon(startPosition, baseAxonParameters, constraintsEncountered),
          m_randomDirectionAxonParameters(randomDirectionAxonParameters) {
}

void RandomDirectionAxon::grow() {
    auto directionVector = sampleVector();
    if (m_tipPositions.size() > 1) {
        auto lastVector = m_tipPositions.back() - m_tipPositions.at(m_tipPositions.size() - 2);
        while (HelperFunctions::checkForDirectionSimilarity(-1 * lastVector, directionVector,
                                                            m_randomDirectionAxonParameters.angleBackwardThreshold)) {
            directionVector = sampleVector();
        }
    }
    auto growthVector = directionVector * m_randomDirectionAxonParameters.lengthSampler->sample();
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), growthVector, parameters.minDistance);

    if (!m_baseAxonParameters.constraintManager->checkForConstraint(centers, m_identifier, m_tipPositions.size())) {
        m_tipPositions.emplace_back(m_tipPositions.back() + directionVector);

        if (checkIfBranching() && m_tipPositions.size() > 3) {
            setUpNewBranch();
        }
    } else {
        m_constraintCounter++;
        if (m_constraintCounter > m_baseAxonParameters.maxNumberOfConstraintEncounters) { stopAxon(); }
    }
}

bool RandomDirectionAxon::addPosition(EuclideanVector position) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          parameters.minDistance);
    if (m_baseAxonParameters.constraintManager->checkForConstraint(centers)) {
        m_tipPositions.push_back(position);
    } else {
        return false;
    }
    m_baseAxonParameters.constraintManager->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    return true;
}

EuclideanVector RandomDirectionAxon::sampleVector() {
    return EuclideanVector(m_normalDistribution(*m_generator), m_normalDistribution(*m_generator),
                           m_normalDistribution(*m_generator)).CreateUnitVector();
}

void RandomDirectionAxon::setUpNewBranch() {
    auto size = m_tipPositions.size();
    auto crossProductVector = crossProduct(m_tipPositions.at(size - 1) - m_tipPositions.at(size - 2),
                                           m_tipPositions.at(size - 2) - m_tipPositions.at(size - 3));
    if (auto simulationManager = m_baseAxonParameters.simulationManager.lock()) {
        simulationManager->addStartedAxon(m_tipPositions.at(size - 1), m_tipPositions.at(size - 1) + (
                2 * parameters.minDistance * crossProductVector.CreateUnitVector()), m_constraintCounter);
    }
}
