//
// Created by florian on 10/10/21.
//

#include "RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include "../../Managers/ConstraintManager.h"

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions, int maxConstraintEncounters,
                         double alpha, double beta,
                         double stepLength, EuclideanVector startPosition, ConstraintManagerHandle constraintManager)
        : BaseAxon(startPosition, constraintManager),
          m_GrowthStepsEachTimeStep(numberOfGrowthStepsEachTimeStep),
          m_numberOfRetractions(numberOfRetractions), m_maxConstraintEncounters(maxConstraintEncounters),
          m_alpha(alpha), m_beta(beta),
          m_stepLength(stepLength) {
    m_growthAngles.push_back(std::make_pair<double, double>(0, 0));
    m_timeStepIndices.push_back(1);
}

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions, int maxConstraintEncounters,
                         double alpha, double beta,
                         double stepLength, EuclideanVector startPosition, EuclideanVector nextPosition,
                         ConstraintManagerHandle constraintManager) : BaseAxon(startPosition, nextPosition,
                                                                               constraintManager),
                                                                      m_GrowthStepsEachTimeStep(
                                                                              numberOfGrowthStepsEachTimeStep),
                                                                      m_numberOfRetractions(numberOfRetractions),
                                                                      m_maxConstraintEncounters(
                                                                              maxConstraintEncounters),
                                                                      m_alpha(alpha), m_beta(beta), m_stepLength(
                stepLength) {
    m_growthAngles.push_back(std::make_pair<double, double>(0, 0));
    m_timeStepIndices.push_back(2);
}

void RazettiAxon::grow() {
    std::list<std::vector<EuclideanVector>> centersCurrentTimeStep;
    std::list<EuclideanVector> tipPositionsCurrentTimeStep;
    tipPositionsCurrentTimeStep.push_back(m_tipPositions.back());
    auto growthStep = 0;
    auto constraintEncountersCurrentTimeStep = 0;
    while (growthStep < m_GrowthStepsEachTimeStep &&
           constraintEncountersCurrentTimeStep < m_maxConstraintsEachTimeStep) {
        growthStep++;
        auto growthVector = sampleVector();
        centersCurrentTimeStep.push_back(
                HelperFunctions::createCoveringCenters(tipPositionsCurrentTimeStep.back(), growthVector,
                                                       parameters.minDistance));


        if (!m_constraintHandler->checkForConstraint(centersCurrentTimeStep.back())) {

            tipPositionsCurrentTimeStep.emplace_back(tipPositionsCurrentTimeStep.back() + growthVector);


        } else {
            constraintEncountersCurrentTimeStep++;
            auto retractions = std::min(m_numberOfRetractions, growthStep);
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
    m_numberOfGrowthTimes++;

    m_tipPositions.insert(m_tipPositions.end(), ++tipPositionsCurrentTimeStep.begin(),
                          tipPositionsCurrentTimeStep.end());
    m_timeStepIndices.push_back(m_timeStepIndices.back() + tipPositionsCurrentTimeStep.size());
}

EuclideanVector RazettiAxon::sampleVector() {
    auto expectation_0 = (m_alpha / (m_alpha + m_beta)) * m_growthAngles.back().first;
    auto variation_0 = 1 / sqrt(2 * (m_alpha + m_beta));
    auto newTheta0 = std::normal_distribution<>(expectation_0, variation_0)(parameters.m_generator);

    auto expectation_1 = (m_alpha / (m_alpha + m_beta)) * m_growthAngles.back().second;
    auto variation_1 = 1 / sqrt(2 * (m_alpha + m_beta));
    auto newTheta1 = std::normal_distribution<>(expectation_1, variation_1)(parameters.m_generator);

    auto finalAngle_0 = 2 * atan(newTheta0);
    auto finalAngle_1 = 2 * atan(newTheta1);

    auto growthVector = HelperFunctions::sph2cart(
            finalAngle_0, finalAngle_1, m_stepLength);
    m_growthAngles.emplace_back(newTheta0, newTheta1);
    return growthVector;
}

void RazettiAxon::checkStopCondition() {
    if (m_constraintCounter > m_maxConstraintEncounters) { stopAxon(); }
}

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions, int maxConstraintEncounters,
                         double alpha, double beta,
                         double stepLength, const EuclideanVector &startPosition,
                         std::pair<double, double> startingAngles, ConstraintManagerHandle constraintManager)
        : BaseAxon(startPosition,
                   std::move(constraintManager)),
          m_GrowthStepsEachTimeStep(
                  numberOfGrowthStepsEachTimeStep),
          m_numberOfRetractions(numberOfRetractions), m_maxConstraintEncounters(maxConstraintEncounters),
          m_alpha(alpha), m_beta(beta),
          m_stepLength(stepLength) {
    m_growthAngles.push_back(startingAngles);
    m_timeStepIndices.push_back(1);
}
