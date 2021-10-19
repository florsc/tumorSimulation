//
// Created by florian on 10/12/21.
//

#include "RazettiFactory.h"

#include "../AxonTypes/RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include <cmath>

RazettiFactory::RazettiFactory(int numberOfGrowthStepsEachTimeStep,
                               int numberOfRetractions, int maxNumberOfConstraintEncounters, double alpha, double beta,
                               SamplerHandle lengthSampler, SimulationManagerHandle simulationManagerHandle)
        : AxonFactory(simulationManagerHandle),
          m_numberOfGrowthStepsEachTimeStep(numberOfGrowthStepsEachTimeStep),
          m_numberOfRetractions(numberOfRetractions),
          m_maxNumberOfConstraintEncounters(maxNumberOfConstraintEncounters),
          m_alpha(alpha), m_beta(beta), m_lengthSampler(lengthSampler) {

}

AxonHandle RazettiFactory::makeAxon(const EuclideanVector &startPosition) {
    return AxonHandle(
            new RazettiAxon(m_numberOfGrowthStepsEachTimeStep, m_numberOfRetractions, m_maxNumberOfConstraintEncounters,
                            m_alpha, m_beta, m_lengthSampler,
                            startPosition, m_constraintManager, m_simulationManager));
}

AxonHandle RazettiFactory::makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) {
    auto axon = std::make_shared<RazettiAxon>(m_numberOfGrowthStepsEachTimeStep, m_numberOfRetractions,
                                              m_maxNumberOfConstraintEncounters,
                                              m_alpha, m_beta, m_lengthSampler,
                                              startPosition, m_constraintManager, m_simulationManager);
    auto angles = HelperFunctions::getSphericalAngles(nextPosition - startPosition);
    axon->addPosition(nextPosition, angles);
    return axon;
}
