//
// Created by florian on 10/10/21.
//

#include "RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include "../../Managers/ConstraintManager.h"
#include "../../Managers/SimulationManager.h"
#include "../../util/Samplers.h"

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int maxConstraintsEachGrowthStep,
                         int maxConstraintEncounters,
                         double alpha, double beta,
                         SamplerHandle lengthSampler, EuclideanVector startPosition,
                         ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager)
        : BaseAxon(startPosition, maxConstraintsEachGrowthStep, constraintManager, simulationManager),
          m_substepsEachGrowthStep(numberOfGrowthStepsEachTimeStep), m_maxConstraintEncounters(maxConstraintEncounters),
          m_alpha(alpha), m_beta(beta),
          m_lengthSampler(lengthSampler) {
    m_growthAngles.push_back(std::make_pair<double, double>(0, 0));
    m_growthStepIndices.push_back(1);
}

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int maxConstraintsEachGrowthStep,
                         int maxConstraintEncounters,
                         double alpha, double beta,
                         SamplerHandle lengthSampler, EuclideanVector startPosition, EuclideanVector nextPosition,
                         ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager)
        : BaseAxon(startPosition, nextPosition, maxConstraintsEachGrowthStep,
                   constraintManager, simulationManager),
          m_substepsEachGrowthStep(
                  numberOfGrowthStepsEachTimeStep),

          m_maxConstraintEncounters(
                  maxConstraintEncounters),
          m_alpha(alpha), m_beta(beta), m_lengthSampler(
                lengthSampler) {
    m_growthAngles.push_back(std::make_pair<double, double>(0, 0));
    m_growthStepIndices.push_back(2);
}

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int maxConstraintsEachGrowthStep,
                         int maxConstraintEncounters,
                         double alpha, double beta,
                         SamplerHandle lengthSampler, const EuclideanVector &startPosition,
                         std::pair<double, double> startingAngles, ConstraintManagerHandle constraintManager,
                         SimulationManagerHandle simulationManager)
        : BaseAxon(startPosition, maxConstraintsEachGrowthStep,
                   std::move(constraintManager), simulationManager),
          m_substepsEachGrowthStep(
                  numberOfGrowthStepsEachTimeStep), m_maxConstraintEncounters(maxConstraintEncounters),
          m_alpha(alpha), m_beta(beta),
          m_lengthSampler(lengthSampler) {
    m_growthAngles.push_back(startingAngles);
    m_growthStepIndices.push_back(1);
}

void RazettiAxon::grow() {
    std::list<std::vector<EuclideanVector>> centersCurrentTimeStep;
    PositionVector tipPositionsCurrentTimeStep;
    tipPositionsCurrentTimeStep.reserve(m_numberOfGrowthTimes);
    tipPositionsCurrentTimeStep.push_back(m_tipPositions.back());
    auto growthStep = 0;
    auto constraintEncountersCurrentTimeStep = 0;
    while (growthStep < m_substepsEachGrowthStep &&
           constraintEncountersCurrentTimeStep < m_maxConstraintsEachGrowthStep) {
        growthStep++;
        auto growthVector = sampleVector();
        centersCurrentTimeStep.push_back(
                HelperFunctions::createCoveringCenters(tipPositionsCurrentTimeStep.back(), growthVector,
                                                       parameters.minDistance));


        if (!m_constraintHandler->checkForConstraint(centersCurrentTimeStep.back())) {

            tipPositionsCurrentTimeStep.emplace_back(tipPositionsCurrentTimeStep.back() + growthVector);


        } else {
            constraintEncountersCurrentTimeStep++;
            auto retractions = std::min(m_maxConstraintsEachGrowthStep, growthStep);
            HelperFunctions::removeElementsFromEnd(centersCurrentTimeStep, retractions);
            HelperFunctions::removeElementsFromEnd(tipPositionsCurrentTimeStep, retractions - 1);
            HelperFunctions::removeElementsFromEnd(m_growthAngles, retractions);
            m_constraintCounter++;
            checkStopCondition();
            growthStep = growthStep - retractions;
        }
    }
    for (const auto &centers: centersCurrentTimeStep) {
        m_constraintHandler->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    }
    if (checkBranching() && tipPositionsCurrentTimeStep.size() > 2) {
        createNewBranch(tipPositionsCurrentTimeStep);
    }
    m_numberOfGrowthTimes++;

    m_tipPositions.insert(m_tipPositions.end(), ++tipPositionsCurrentTimeStep.begin(),
                          tipPositionsCurrentTimeStep.end());
    m_growthStepIndices.push_back(m_growthStepIndices.back() + tipPositionsCurrentTimeStep.size());
}

EuclideanVector RazettiAxon::sampleVector() {
    auto expectation_0 = (m_alpha / (m_alpha + m_beta)) * m_growthAngles.back().first;
    auto variation_0 = 1 / sqrt(2 * (m_alpha + m_beta));
    auto newTheta0 = std::normal_distribution<>(expectation_0, variation_0)(*m_generator);

    auto expectation_1 = (m_alpha / (m_alpha + m_beta)) * m_growthAngles.back().second;
    auto variation_1 = 1 / sqrt(2 * (m_alpha + m_beta));
    auto newTheta1 = std::normal_distribution<>(expectation_1, variation_1)(*m_generator);

    auto finalAngle_0 = 2 * atan(newTheta0);
    auto finalAngle_1 = 2 * atan(newTheta1);

    auto growthVector = HelperFunctions::sph2cart(
            finalAngle_0, finalAngle_1, m_lengthSampler->sample());
    m_growthAngles.emplace_back(newTheta0, newTheta1);
    return growthVector;
}

void RazettiAxon::checkStopCondition() {
    if (m_constraintCounter > m_maxConstraintEncounters) { stopAxon(); }
}

bool RazettiAxon::checkBranching() {
    bool branch = std::bernoulli_distribution(parameters.branchingProbability)(*m_generator);
    return branch;
}

void RazettiAxon::createNewBranch(const PositionVector &possibleStartingPoints) {
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
        auto growthVector = HelperFunctions::sph2cart(az, el, m_lengthSampler->sample());
        nextPosition = startPosition + growthVector;
        tries++;
        centers = HelperFunctions::createCoveringCenters(startPosition, growthVector,
                                                         parameters.minDistance);
    } while (m_constraintHandler->checkForConstraint(centers) && tries < 20);
    if (tries < 20) {
        if (auto simulationManager = m_simulationManager.lock()) {
            simulationManager->addStartedAxon(startPosition, nextPosition);
        }
    }
}

bool RazettiAxon::addPosition(EuclideanVector position) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          parameters.minDistance);
    if (m_constraintHandler->checkForConstraint(centers)) {
        m_tipPositions.push_back(position);
        m_growthAngles.push_back(m_growthAngles.back());
    } else {
        return false;
    }
    m_constraintHandler->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    m_growthStepIndices.push_back(m_growthStepIndices.back() + 1);
    return true;
}

bool RazettiAxon::addPosition(EuclideanVector position, std::pair<double, double> angles) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          parameters.minDistance);
    if (m_constraintHandler->checkForConstraint(centers)) {
        m_tipPositions.push_back(position);
        m_growthAngles.push_back(angles);
    } else {
        return false;
    }
    m_constraintHandler->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    m_growthStepIndices.push_back(m_growthStepIndices.back() + 1);
    return true;

}
