//
// Created by florian on 10/12/21.
//

#include "RazettiFactory.h"

#include "../AxonTypes/RazettiAxon/RazettiAxon.h"
#include "../../util/HelperFunctions.h"

RazettiFactory::RazettiFactory(RazettiSetUpParametersHandle razettiSetUpParameters) : AxonFactory(
        razettiSetUpParameters), m_razettiAxonParameters(razettiSetUpParameters), m_startAngleSampler(
        razettiSetUpParameters->startAngleSampler) {

}

AxonHandle
RazettiFactory::makeAxon(const EuclideanVector &startPosition, int constraintsEncountered, WeakAxonHandle rootAxon) {
    auto axon = std::make_shared<RazettiAxon>(startPosition, m_axonIdentifier++, m_razettiAxonParameters,
                                              m_baseAxonParameters,
                                              std::make_pair<double, double>(m_startAngleSampler->sample(),
                                                                             m_startAngleSampler->sample()),
                                              constraintsEncountered);
    setUpRoot(axon, rootAxon);
    return axon;
}

AxonHandle RazettiFactory::makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                                           int constraintsEncountered, WeakAxonHandle rootAxon) {
    auto axon = std::make_shared<RazettiAxon>(startPosition, m_axonIdentifier++, m_razettiAxonParameters,
                                              m_baseAxonParameters, std::make_pair<double, double>(0, 0),
                                              constraintsEncountered);
    auto angles = HelperFunctions::getSphericalAngles(nextPosition - startPosition);
    axon->addPosition(nextPosition, angles);
    setUpRoot(axon, rootAxon);
    return axon;
}
