//
// Created by florian on 10/10/21.
//

#include "RazettiAxon.h"

#include <utility>
#include "../../../util/HelperFunctions.h"
#include "../../../Managers/ConstraintManager.h"
#include "../../../Managers/SimulationManager.h"
#include "../../../util/Samplers.h"

RazettiAxon::RazettiAxon(const EuclideanVector &startPosition,
                         RazettiAxonParameters razettiAxonParameters, BaseAxonParameters baseAxonParameters,
                         int constraintsEncountered)
        : BaseAxon(startPosition, baseAxonParameters, constraintsEncountered),
          m_razettiAxonParameters(razettiAxonParameters) {
    m_growthAngles.push_back(std::make_pair<double, double>(0, 0));
    m_growthStepIndices.push_back(1);
}

RazettiAxon::RazettiAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                         RazettiAxonParameters razettiAxonParameters, BaseAxonParameters baseAxonParameters,
                         int constraintsEncountered)
        : BaseAxon(startPosition, nextPosition, baseAxonParameters, constraintsEncountered),
          m_razettiAxonParameters(razettiAxonParameters) {
    m_growthAngles.push_back(std::make_pair<double, double>(0, 0));
    m_growthStepIndices.push_back(2);
}


void RazettiAxon::grow() {
    std::list<PositionVector> centersCurrentTimeStep;
    PositionVector tipPositionsCurrentTimeStep;
    tipPositionsCurrentTimeStep.reserve(m_numberOfGrowthTimes);
    tipPositionsCurrentTimeStep.push_back(m_tipPositions.back());
    auto growthStep = 0;
    auto constraintEncountersCurrentTimeStep = 0;
    while (growthStep < m_razettiAxonParameters.numberOfSubstepsEachStep &&
           constraintEncountersCurrentTimeStep < m_razettiAxonParameters.maxNumberOfConstraintEncountersEachSubstep &&
           m_active) {
        growthStep++;
        auto growthVector = sampleVector();
        centersCurrentTimeStep.push_back(
                HelperFunctions::createCoveringCenters(tipPositionsCurrentTimeStep.back(), growthVector,
                                                       ParameterStruct::minDistance));


        if (!checkConstraints(centersCurrentTimeStep.back())) {

            tipPositionsCurrentTimeStep.emplace_back(tipPositionsCurrentTimeStep.back() + growthVector);
            checkTargetReached(tipPositionsCurrentTimeStep.back() + growthVector);

        } else {
            constraintEncountersCurrentTimeStep++;
            auto retractions = std::min(m_razettiAxonParameters.numberOfRetractions, growthStep);
            HelperFunctions::removeElementsFromEnd(centersCurrentTimeStep, retractions);
            HelperFunctions::removeElementsFromEnd(tipPositionsCurrentTimeStep, retractions - 1);
            HelperFunctions::removeElementsFromEnd(m_growthAngles, retractions);
            m_constraintCounter++;
            checkStopCondition();
            growthStep = growthStep - retractions;
        }
    }
    PositionVector flatVector;
    for (const auto &centers: centersCurrentTimeStep) {
        flatVector.insert(flatVector.end(),centers.begin(),centers.end());
    }
    m_baseAxonParameters.constraintManager->addConstraintCenters(flatVector, m_identifier, m_numberOfGrowthTimes);

    if (checkIfBranching() && tipPositionsCurrentTimeStep.size() > 2) {
        setUpNewBranch(tipPositionsCurrentTimeStep);
    }
    m_numberOfGrowthTimes++;

    m_tipPositions.insert(m_tipPositions.end(), ++tipPositionsCurrentTimeStep.begin(),
                          tipPositionsCurrentTimeStep.end());
    m_growthStepIndices.push_back(m_growthStepIndices.back() + tipPositionsCurrentTimeStep.size());
}

EuclideanVector RazettiAxon::sampleVector() {
    auto expectation_0 =
            (m_razettiAxonParameters.alpha / (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta)) *
            m_growthAngles.back().first;
    auto variation_0 = 1 / sqrt(2 * (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta));
    auto newTheta0 = std::normal_distribution<>(expectation_0, variation_0)(*m_generator);

    auto expectation_1 =
            (m_razettiAxonParameters.alpha / (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta)) *
            m_growthAngles.back().second;
    auto variation_1 = 1 / sqrt(2 * (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta));
    auto newTheta1 = std::normal_distribution<>(expectation_1, variation_1)(*m_generator);

    auto finalAngle_0 = 2 * atan(newTheta0);
    auto finalAngle_1 = 2 * atan(newTheta1);

    auto growthVector = HelperFunctions::sph2cart(
            finalAngle_0, finalAngle_1, m_razettiAxonParameters.lengthSampler->sample());
    m_growthAngles.emplace_back(newTheta0, newTheta1);
    return growthVector;
}

void RazettiAxon::setUpNewBranch(const PositionVector &possibleStartingPoints) {
    auto positionIndex = std::uniform_int_distribution<int>(1, possibleStartingPoints.size() - 1)(
            *m_generator);
    auto startPosition = possibleStartingPoints[positionIndex];
    auto initialAzDistribution = std::uniform_real_distribution<double>(0, 2 * M_PI);
    auto initialElDistribution = std::uniform_real_distribution<double>(-0.5 * M_PI, 0.5 * M_PI);
    double az;
    double el;
    EuclideanVector nextPosition;
    std::vector<EuclideanVector> centers;
    auto tries = 0;
    do {
        az = initialAzDistribution(*m_generator);
        el = initialElDistribution(*m_generator);
        auto growthVector = HelperFunctions::sph2cart(az, el, m_razettiAxonParameters.lengthSampler->sample());
        nextPosition = startPosition + growthVector;
        tries++;
    } while (createBranchIfPossible(startPosition, nextPosition) && tries < 20);
}

bool RazettiAxon::addPosition(const EuclideanVector &position) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          ParameterStruct::minDistance);
    if (m_baseAxonParameters.constraintManager->checkForConstraint(centers)) {
        m_tipPositions.push_back(position);
        m_growthAngles.push_back(m_growthAngles.back());
    } else {
        return false;
    }
    m_baseAxonParameters.constraintManager->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    m_growthStepIndices.push_back(m_growthStepIndices.back() + 1);
    return true;
}

bool RazettiAxon::addPosition(const EuclideanVector &position, std::pair<double, double> angles) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          parameters.minDistance);
    if (m_baseAxonParameters.constraintManager->checkForConstraint(centers)) {
        m_tipPositions.push_back(position);
        m_growthAngles.push_back(angles);
    } else {
        return false;
    }
    m_baseAxonParameters.constraintManager->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    m_growthStepIndices.push_back(m_growthStepIndices.back() + 1);
    return true;

}
