//
// Created by florian on 9/23/21.
//

#ifndef TUMORSIMULATION_SAMPLER_H
#define TUMORSIMULATION_SAMPLER_H


#include <random>
#include <chrono>
#include <memory>
#include <queue>
#include "Axon.h"
#include "ParameterStruct.h"


class Sampler {
protected:
    std::mt19937 m_generator;
    std::uniform_real_distribution<double> m_uniformSampler;
    std::normal_distribution<> m_normalSampler;
    bool m_processWithWaitingTime;
public:
    explicit Sampler( bool waitingTime=false, std::mt19937 generator = std::mt19937(
            std::chrono::system_clock::now().time_since_epoch().count()));

    virtual double sampleLength() {};

    virtual double sampleWaitingTime() { return 0.0;};

    virtual bool waitingTimeIsUsed(){return m_processWithWaitingTime;}

    virtual std::pair<double, int> getNextAxon() { return {}; }

    bool branch();

    double getUniformSample() { return m_uniformSampler(m_generator); };

    double getNormalSample() { return m_normalSampler(m_generator); };

};

class WaitingTimeSampler{
public:
    virtual double sampleWaitingTime() = 0;
};

class LengthSampler{
public:
    virtual double sampleLength() = 0;
};
class uniformLengthNoWaitingTimeSampler : public Sampler {
    std::uniform_real_distribution<double> m_lengthSampler;

public:
    uniformLengthNoWaitingTimeSampler(double low, double high);

    double sampleLength() override;
};

class constantLengthNoWaitingTimeSampler : public Sampler {
    double m_length;
public:
    explicit constantLengthNoWaitingTimeSampler(double length);

    double sampleLength() override;
};



class biasedRandomWalk : public Sampler {
    std::uniform_real_distribution<double> m_waitingTimeSampler;
public:
    explicit biasedRandomWalk();

    double sampleLength() override;
    double sampleWaitingTime() override {return m_waitingTimeSampler(m_generator);}
};

#endif //TUMORSIMULATION_SAMPLER_H
