//
// Created by florian on 10/10/21.
//

#include "RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include "../../Managers/ConstraintManager.h"
#include "../../Managers/SimulationManager.h"

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions, int maxConstraintEncounters,
                         double alpha, double beta,
                         double stepLength, EuclideanVector startPosition, ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager)
        : BaseAxon(startPosition, constraintManager, simulationManager),
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
                         ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager) : BaseAxon(startPosition, nextPosition,
                                                                               constraintManager, simulationManager),
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

RazettiAxon::RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions, int maxConstraintEncounters,
                         double alpha, double beta,
                         double stepLength, const EuclideanVector &startPosition,
                         std::pair<double, double> startingAngles, ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager)
        : BaseAxon(startPosition,
                   std::move(constraintManager), simulationManager),
          m_GrowthStepsEachTimeStep(
                  numberOfGrowthStepsEachTimeStep),
          m_numberOfRetractions(numberOfRetractions), m_maxConstraintEncounters(maxConstraintEncounters),
          m_alpha(alpha), m_beta(beta),
          m_stepLength(stepLength) {
    m_growthAngles.push_back(startingAngles);
    m_timeStepIndices.push_back(1);
}

void RazettiAxon::grow() {
    std::list<std::vector<EuclideanVector>> centersCurrentTimeStep;
    PositionVector tipPositionsCurrentTimeStep;
    tipPositionsCurrentTimeStep.reserve(m_numberOfGrowthTimes);
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
    if(checkBranching() && tipPositionsCurrentTimeStep.size()>2){
        createNewBranch(tipPositionsCurrentTimeStep);
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

bool RazettiAxon::checkBranching() {
    bool branch = std::bernoulli_distribution(parameters.branchingProbability)(parameters.m_generator);
    return branch;
}

void RazettiAxon::createNewBranch(const PositionVector& possibleStartingPoints) {
    auto positionIndex = std::uniform_int_distribution<int>(1,possibleStartingPoints.size()-1)(parameters.m_generator);
    auto startPosition = possibleStartingPoints[positionIndex];
    auto initialAzDistribution = std::uniform_real_distribution<double>(0,2*M_PI);
    auto initialElDistribution = std::uniform_real_distribution<double>(-0.5*M_PI,0.5*M_PI);
    double az;
    double el;
    EuclideanVector nextPosition;
    std::vector<EuclideanVector> centers;
    auto tries = 0;
    do{
        az = initialAzDistribution(parameters.m_generator);
        el = initialElDistribution(parameters.m_generator);
        auto growthVector = HelperFunctions::sph2cart(az,el,m_stepLength);
        nextPosition = startPosition+growthVector;
        tries++;
        centers = HelperFunctions::createCoveringCenters(startPosition, growthVector,
                                                       parameters.minDistance);
    }while(m_constraintHandler->checkForConstraint(centers) && tries <20);
    if(tries<20){
        if(auto simulationManager = m_simulationManager.lock()){
        simulationManager->addStartedAxon(startPosition, nextPosition);
    }}
}

void RazettiAxon::addPosition(EuclideanVector position) {
    m_tipPositions.push_back(position);
    m_growthAngles.push_back(m_growthAngles.back());
}

void RazettiAxon::addPosition(EuclideanVector position, std::pair<double, double> angles) {
    m_tipPositions.push_back(position);
    m_growthAngles.push_back(angles);
}
