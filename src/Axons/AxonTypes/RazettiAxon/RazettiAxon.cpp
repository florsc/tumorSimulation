//
// Created by florian on 10/10/21.
//

#include "RazettiAxon.h"

#include <utility>
#include "../../../util/HelperFunctions.h"
#include "../../../Managers/ConstraintManager.h"
#include "../../../Managers/SimulationManager.h"
#include "../../../util/Samplers.h"
#include "../../../Managers/TargetManager.h"

RazettiAxon::RazettiAxon(const EuclideanVector &startPosition, int id,
                         RazettiAxonParameters razettiAxonParameters, BaseAxonParameters baseAxonParameters,
                         int constraintsEncountered)
        : BaseAxon(startPosition, id, std::move(baseAxonParameters), constraintsEncountered),
          m_razettiAxonParameters(std::move(razettiAxonParameters)) {
    m_growthAnglesParameters.push_back(parameters.startAngles);
    m_growthStepIndices.push_back(1);
}

RazettiAxon::RazettiAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition, int id,
                         RazettiAxonParameters razettiAxonParameters, BaseAxonParameters baseAxonParameters,
                         int constraintsEncountered)
        : BaseAxon(startPosition, nextPosition, id, std::move(baseAxonParameters), constraintsEncountered),
          m_razettiAxonParameters(std::move(razettiAxonParameters)) {
    m_growthAnglesParameters.push_back(std::make_pair<double, double>(std::uniform_real_distribution<>(0.0, M_PI)(*m_generator), std::uniform_real_distribution<>(0.0, 2*M_PI)(*m_generator)));
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
        auto growthVector = sampleVector(0.75);
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
            HelperFunctions::removeElementsFromEnd(m_growthAnglesParameters, retractions);
            m_constraintCounter++;
            checkForStopping();
            growthStep = growthStep - retractions;
        }
    }
    PositionVector flatVector;
    for (const auto &centers: centersCurrentTimeStep) {
        flatVector.insert(flatVector.end(),centers.begin(),centers.end());
    }
    m_baseAxonParameters.constraintManager->addConstraintCenters(flatVector, m_identifier, m_numberOfGrowthTimes);

    if (m_active&&checkIfBranching() && tipPositionsCurrentTimeStep.size() > 2) {
        setUpNewBranch(tipPositionsCurrentTimeStep);
    }
    m_numberOfGrowthTimes++;
    auto tmp = m_tipPositions.back();
    for(const auto& step:tipPositionsCurrentTimeStep){
        m_length +=(tmp-step).GetEuclideanNorm();
        tmp = step;
    }
    m_tipPositions.insert(m_tipPositions.end(), ++tipPositionsCurrentTimeStep.begin(),
                          tipPositionsCurrentTimeStep.end());
    m_growthStepIndices.push_back(m_growthStepIndices.back() + tipPositionsCurrentTimeStep.size());

    checkLength();
}

bool RazettiAxon::addPosition(const EuclideanVector &position) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          ParameterStruct::minDistance);
    if (m_baseAxonParameters.constraintManager->checkForConstraint(centers)) {
        m_length += (m_tipPositions.back()-position).GetEuclideanNorm();
        m_tipPositions.push_back(position);
        m_growthAnglesParameters.push_back(m_growthAnglesParameters.back());
    } else {
        return false;
    }
    m_baseAxonParameters.constraintManager->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    m_growthStepIndices.push_back(m_growthStepIndices.back() + 1);

    checkLength();
    return true;
}

bool RazettiAxon::addPosition(const EuclideanVector &position, std::pair<double, double> angles) {
    auto centers = HelperFunctions::createCoveringCenters(m_tipPositions.back(), position - m_tipPositions.back(),
                                                          ParameterStruct::minDistance);
    //if (m_baseAxonParameters.constraintManager->checkForConstraint(centers)) {
    m_length += (m_tipPositions.back()-position).GetEuclideanNorm();
        m_tipPositions.push_back(position);
        m_growthAnglesParameters.push_back(angles);
    //} else {
//std::cout<<"a"<<std::endl;
      //  return false;
    //}
    m_baseAxonParameters.constraintManager->addConstraintCenters(centers, m_identifier, m_numberOfGrowthTimes);
    m_numberOfGrowthTimes++;

    m_growthStepIndices.push_back(m_growthStepIndices.back() + 1);
    checkLength();
    return true;

}
/*
EuclideanVector RazettiAxon::sampleAngles() {
    auto expectation_0 =
            (m_razettiAxonParameters.alpha / (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta)) *
            m_growthAnglesParameters.back().first;
    auto variation_0 = 1 / sqrt(2 * (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta));
    auto newTheta0 = std::normal_distribution<>(expectation_0, variation_0)(*m_generator);

    auto expectation_1 =
            (m_razettiAxonParameters.alpha / (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta)) *
            m_growthAnglesParameters.back().second;
    auto variation_1 = 1 / sqrt(2 * (m_razettiAxonParameters.alpha + m_razettiAxonParameters.beta));
    auto newTheta1 = std::normal_distribution<>(expectation_1, variation_1)(*m_generator);

    auto finalAngle_0 = 2 * atan(newTheta0);
    auto finalAngle_1 = 2 * atan(newTheta1);

    auto growthVector = HelperFunctions::sph2cart(
            finalAngle_0, finalAngle_1, m_razettiAxonParameters.lengthSampler->sample());
    m_growthAnglesParameters.emplace_back(newTheta0, newTheta1);
    return growthVector+m_baseAxonParameters.targetManager->calculateForce(m_tipPositions.back());
}
*/
EuclideanVector RazettiAxon::sampleVector(double angle, bool save, int reverseIndex) {

    std::gamma_distribution<double> dist(m_razettiAxonParameters.beta,m_razettiAxonParameters.beta);
    auto x1 = dist(*m_generator);
    auto angleFraction = x1/(x1+dist(*m_generator));
    auto circularAngle = std::uniform_real_distribution<>(0.0, 2*M_PI)(*m_generator);
    auto deviationAngle = std::abs(angle*M_PI*(angleFraction-0.5));
    //std::cout<<angleFraction<<"a"<<std::endl;
    //std::cout<<circularAngle<<std::endl;
    //std::cout<<deviationAngle<<std::endl;
    auto newAngleAz =atan(sin(deviationAngle)*sin(circularAngle)/cos(deviationAngle));
    auto newAngleEl =(atan(sin(deviationAngle)*cos(circularAngle)/sqrt(
            (pow(cos(deviationAngle),2)+(pow(sin(deviationAngle)*sin(circularAngle),2))))));

/*
    std::gamma_distribution<double> dist(m_razettiAxonParameters.beta,m_razettiAxonParameters.beta);
    auto x1 = dist(*m_generator);
    auto x2 = dist(*m_generator);
    auto newAngle0 = (x1/(x1+dist(*m_generator))-0.5)*angle*M_PI;
    auto newAngle1 = (x2/(x2+dist(*m_generator))-0.5)*angle*M_PI;
*/

    //auto newAngle0 = std::uniform_real_distribution<>(-0.2*M_PI, 0.2*M_PI)(*m_generator);
    //auto newAngle1 = std::uniform_real_distribution<>(-0.2*M_PI, 0.2*M_PI)(*m_generator);

    auto finalAngle_El = m_growthAnglesParameters.end()[-reverseIndex].first + newAngleEl;
    auto finalAngle_Az = m_growthAnglesParameters.end()[-reverseIndex].second+newAngleAz;
    if(finalAngle_El<0){finalAngle_El = -finalAngle_El;
        finalAngle_Az += M_PI;
    }
    if(finalAngle_El>M_PI){finalAngle_El = 2*M_PI-finalAngle_El;
        finalAngle_Az += M_PI;
    }

    while(finalAngle_Az>2*M_PI){finalAngle_Az = finalAngle_Az-2*M_PI;}
    while(finalAngle_Az<0){finalAngle_Az = finalAngle_Az+2*M_PI;}
    auto growthVector = HelperFunctions::sph2cart(
            finalAngle_Az, finalAngle_El, m_razettiAxonParameters.lengthSampler->sample());
    if(save){
    m_growthAnglesParameters.emplace_back(finalAngle_El, finalAngle_Az);
}
    return growthVector;//+m_baseAxonParameters.targetManager->calculateForce(m_tipPositions.back());
}

void RazettiAxon::setUpNewBranch(const PositionVector &possibleStartingPoints) {
    if(m_numberOfBranches<ParameterStruct::maxNumberOfBranches) {
        auto positionIndex = std::uniform_int_distribution<int>(1, possibleStartingPoints.size() - 1)(
                *m_generator);
        auto startPosition = possibleStartingPoints[positionIndex];
        auto initialAzDistribution = std::uniform_real_distribution<double>(0, 2 * M_PI);
        auto initialElDistribution = std::uniform_real_distribution<double>(0, M_PI);
        double az;
        double el;
        EuclideanVector nextPosition;
        std::vector<EuclideanVector> centers;
        auto tries = 0;
        do {
            az = initialAzDistribution(*m_generator);
            el = initialElDistribution(*m_generator);
            auto growthVector = sampleVector(0.75,false, possibleStartingPoints.size()-positionIndex+1);//HelperFunctions::sph2cart(az, el, 1);//m_razettiAxonParameters.lengthSampler->sample());
            nextPosition = startPosition + growthVector;
            tries++;

        } while (!createBranchIfPossible(startPosition, nextPosition) && tries < 20);
    }
}


