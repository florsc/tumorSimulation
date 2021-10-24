//
// Created by florian on 10/18/21.
//

#include "RandomDirectionFactory.h"
//
// Created by florian on 10/12/21.
//

#include "RazettiFactory.h"

#include "../AxonTypes/RazettiAxon/RazettiAxon.h"
#include "../../util/HelperFunctions.h"
#include "../AxonTypes/RandomDirectionAxon/RandomDirectionAxon.h"
#include <cmath>

RandomDirectionFactory::RandomDirectionFactory() : AxonFactory() {}

AxonHandle RandomDirectionFactory::makeAxon(const EuclideanVector &startPosition, int constraintsEncountered,
                                            WeakAxonHandle rootAxon) {
    auto axon = AxonHandle(
            new RandomDirectionAxon(
                    startPosition, m_randomDirectionAxonParameters, m_baseAxonParameters, constraintsEncountered));
    setUpRoot(axon, rootAxon);
    return axon;
}

AxonHandle
RandomDirectionFactory::makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                                        int constraintsEncountered, WeakAxonHandle rootAxon) {
    auto axon = std::make_shared<RandomDirectionAxon>(startPosition, m_randomDirectionAxonParameters,
                                                      m_baseAxonParameters, constraintsEncountered);
    axon->addPosition(nextPosition);
    setUpRoot(axon, rootAxon);
    return axon;
}
