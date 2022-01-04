//
// Created by florian on 10/12/21.
//

#ifndef TUMORSIMULATION_AXONFACTORY_H
#define TUMORSIMULATION_AXONFACTORY_H


#include <random>
#include "../../util/TypeDefs.h"
#include "../../SimulationSetUp/GrowthModels/AxonSetUpParameters.h"
#include "../AxonTypes/BaseAxon/BaseAxonParameters.h"

class AxonFactory {

protected:
    BaseAxonParameters m_baseAxonParameters;
    int m_axonIdentifier = 0;
    void setUpRoot(const AxonHandle& axon, const WeakAxonHandle& rootAxon) const;

public:

    void setUpFactory(SimulationManagerHandle simulationManager, double branchingProbability);

    virtual AxonHandle
    makeAxon(const EuclideanVector &startPosition, int constraintsEncountered = 0, WeakAxonHandle rootAxon = WeakAxonHandle())  = 0;

    virtual AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                                       int constraintsEncountered, WeakAxonHandle rootAxon)  = 0;

    //test related
    friend class AxonTest;
};

#endif //TUMORSIMULATION_AXONFACTORY_H
