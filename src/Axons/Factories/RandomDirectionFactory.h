//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONFACTORY_H
#define TUMORSIMULATION_RANDOMDIRECTIONFACTORY_H

#include <iostream>
#include "AxonFactory.h"


class RandomDirectionFactory : public AxonFactory {
    int m_maxNumberOfConstraintEncounters;
    SamplerHandle m_lengthSampler;

public:
    RandomDirectionFactory(int maxNumberOfConstraintEncounters,
                   SamplerHandle lengthSampler, SimulationManagerHandle simulationManagerHandle);

    AxonHandle makeAxon(const EuclideanVector &startPosition) override;

    AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) override;

    ~RandomDirectionFactory(){std::cout<<"RandomDirectionFactory destructed"<<std::endl;}

};


#endif //TUMORSIMULATION_RANDOMDIRECTIONFACTORY_H
