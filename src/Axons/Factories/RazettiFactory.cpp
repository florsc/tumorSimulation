//
// Created by florian on 10/12/21.
//

#include "RazettiFactory.h"

#include "../AxonTypes/RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include <cmath>

RazettiFactory::RazettiFactory(ConstraintManagerHandle constraintManager, int numberOfGrowthStepsEachTimeStep,
                               int numberOfRetractions, int maxNumberOfConstraintEncounters, double alpha, double beta,
                               double stepLength) : AxonFactory(constraintManager),
                                                    m_numberOfGrowthStepsEachTimeStep(numberOfGrowthStepsEachTimeStep),
                                                    m_numberOfRetractions(numberOfRetractions),
                                                    m_maxNumberOfConstraintEncounters(maxNumberOfConstraintEncounters),
                                                    m_alpha(alpha), m_beta(beta), m_stepLength(stepLength) {

}

AxonHandle RazettiFactory::makeAxon(const EuclideanVector &startPosition) {
    return std::shared_ptr<BaseAxon>(
            new RazettiAxon(m_numberOfGrowthStepsEachTimeStep, m_numberOfRetractions, m_alpha, m_beta, m_stepLength,
                            startPosition, m_constraintManager));
}

AxonHandle RazettiFactory::makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) {
    return AxonHandle();
}

AxonHandle RazettiFactory::makeDirectedAxon(const EuclideanVector &startPosition, const EuclideanVector &direction) {
    return AxonHandle();
}
