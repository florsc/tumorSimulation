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

    explicit AxonFactory();

public:
    void setUpFactory(SimulationManagerHandle simulationManager);

    virtual AxonHandle
    makeAxon(const EuclideanVector &startPosition, int constraintsEncountered, WeakAxonHandle rootAxon) = 0;

    virtual AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                                       int constraintsEncountered, WeakAxonHandle rootAxon) = 0;

    void setUpRoot(AxonHandle axon, WeakAxonHandle rootAxon);

    virtual ~AxonFactory() {}
};

/*
class WaitingTimeModel:public AxonFactory{

public:
    virtual double sampleWaitingTIme() = 0;
};


class LengthModel:public AxonFactory{

public:
    virtual double sampleLength() = 0;
};

class UniformLengthUniformWaitingTime: public WaitingTimeModel,LengthModel{
    std::uniform_real_distribution<double> m_waitingTimeSampler;
    std::uniform_real_distribution<double> m_lengthSampler;
public:
    UniformLengthUniformWaitingTime(double lowLength, double highLength,double lowWaitingTime, double highWaitingTime):m_lengthSampler(lowLength,highLength),
                                                                                                                       m_waitingTimeSampler(lowWaitingTime, highWaitingTime){

    }
};
*/
#endif //TUMORSIMULATION_AXONFACTORY_H
