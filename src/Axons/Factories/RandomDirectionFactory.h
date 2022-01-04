//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONFACTORY_H
#define TUMORSIMULATION_RANDOMDIRECTIONFACTORY_H

#include <iostream>
#include "AxonFactory.h"
#include "../AxonTypes/RandomDirectionAxon/RandomDirectionAxonParameters.h"
#include "../../SimulationSetUp/GrowthModels/RandomDirectionSetUpParameters.h"


class RandomDirectionFactory : public AxonFactory {
    RandomDirectionAxonParameters m_randomDirectionAxonParameters;

public:
    RandomDirectionFactory();

    AxonHandle makeAxon(const EuclideanVector &startPosition, int constraintsEncountered = 0,
                        WeakAxonHandle rootAxon = WeakAxonHandle())  override;

    AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                               int constraintsEncountered = 0, WeakAxonHandle rootAxon = WeakAxonHandle())  override;

};


#endif //TUMORSIMULATION_RANDOMDIRECTIONFACTORY_H
