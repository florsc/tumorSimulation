//
// Created by florian on 10/12/21.
//

#ifndef TUMORSIMULATION_RAZETTIFACTORY_H
#define TUMORSIMULATION_RAZETTIFACTORY_H

#include <iostream>
#include "../../SimulationSetUp/GrowthModels/RazettiSetUpParameters.h"
#include "../AxonTypes/RazettiAxon/RazettiAxonParameters.h"
#include "AxonFactory.h"

class RazettiFactory : public AxonFactory {
    RazettiAxonParameters m_razettiAxonParameters;
    SamplerHandle m_startAngleSampler;
public:
    RazettiFactory(RazettiSetUpParametersHandle razettiSetUpParameters);

    AxonHandle makeAxon(const EuclideanVector &startPosition, int constraintsEncountered = 0,
                        WeakAxonHandle rootAxon = WeakAxonHandle()) override;

    AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                               int constraintsEncountered = 0, WeakAxonHandle rootAxon = WeakAxonHandle()) override;

    friend class AxonTest;
};

#endif //TUMORSIMULATION_RAZETTIFACTORY_H
