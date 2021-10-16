//
// Created by florian on 10/12/21.
//

#ifndef TUMORSIMULATION_AXONFACTORY_H
#define TUMORSIMULATION_AXONFACTORY_H


#include <random>
#include "../../util/TypeDefs.h"

class AxonFactory {

protected:
    ConstraintManagerHandle m_constraintManager;

    AxonFactory();

public:
    virtual AxonHandle makeAxon(const EuclideanVector &startPosition) = 0;

    virtual AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) = 0;

    virtual AxonHandle makeDirectedAxon(const EuclideanVector &startPosition, const EuclideanVector &direction) = 0;
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
