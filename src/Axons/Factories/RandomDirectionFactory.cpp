//
// Created by florian on 10/18/21.
//

#include "RandomDirectionFactory.h"
//
// Created by florian on 10/12/21.
//

#include "RazettiFactory.h"

#include "../AxonTypes/RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include "../AxonTypes/RandomDirectionAxon.h"
#include <cmath>

RandomDirectionFactory::RandomDirectionFactory(int maxNumberOfConstraintEncounters,
                                               SamplerHandle lengthSampler,
                                               SimulationManagerHandle simulationManagerHandle, double angleBackwardThreshold) : AxonFactory(
        simulationManagerHandle),
                                                                                                  m_maxNumberOfConstraintEncounters(
                                                                                                          maxNumberOfConstraintEncounters),
                                                                                                  m_lengthSampler(
                                                                                                          lengthSampler), m_angleBackwardThreshold(angleBackwardThreshold) {

}

AxonHandle RandomDirectionFactory::makeAxon(const EuclideanVector &startPosition) {
    return AxonHandle(
            new RandomDirectionAxon(m_maxNumberOfConstraintEncounters, m_angleBackwardThreshold, m_lengthSampler,
                                    startPosition, m_constraintManager, m_simulationManager));
}

AxonHandle
RandomDirectionFactory::makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) {
    auto axon = std::make_shared<RandomDirectionAxon>(m_maxNumberOfConstraintEncounters, m_angleBackwardThreshold,
                                                      m_lengthSampler,
                                                      startPosition, m_constraintManager, m_simulationManager);
    axon->addPosition(nextPosition);
    return axon;
}
