//
// Created by florian on 10/12/21.
//

#include "RazettiFactory.h"

#include "../AxonTypes/RazettiAxon/RazettiAxon.h"
#include "../../util/HelperFunctions.h"

RazettiFactory::RazettiFactory() : AxonFactory() {

}

AxonHandle
RazettiFactory::makeAxon(const EuclideanVector &startPosition, int constraintsEncountered, WeakAxonHandle rootAxon)  {
    auto axon = std::make_shared<RazettiAxon>(startPosition, m_axonIdentifier++, m_razettiAxonParameters, m_baseAxonParameters, constraintsEncountered);
    setUpRoot(axon, rootAxon);
    return axon;
}

AxonHandle RazettiFactory::makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                                           int constraintsEncountered, WeakAxonHandle rootAxon)  {
    auto axon = std::make_shared<RazettiAxon>(startPosition, m_axonIdentifier++, m_razettiAxonParameters, m_baseAxonParameters,
                                              constraintsEncountered);
    auto angles = HelperFunctions::getSphericalAngles(nextPosition - startPosition);
    axon->addPosition(nextPosition, angles);
    setUpRoot(axon, rootAxon);
    return axon;
}
