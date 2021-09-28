//
// Created by florian on 9/23/21.
//

#ifndef TUMORSIMULATION_PROCESSSAMPLER_H
#define TUMORSIMULATION_PROCESSSAMPLER_H


#include <random>
#include <chrono>
#include <memory>
#include <queue>
#include "Axon.h"

class ProcessSampler {
protected:
    std::mt19937 m_generator;
    bool m_sampleWaitingTime;
    std::uniform_real_distribution<double> m_branchSampler;
public:
    explicit ProcessSampler(bool sampleWaitingTime = false, std::mt19937 generator = std::mt19937(
            std::chrono::system_clock::now().time_since_epoch().count()), double branchProbability = 0.05);

    virtual double sampleLength() {};

    virtual bool sampleWaitingTime() { return m_sampleWaitingTime; };

    virtual std::pair<double, int> getNextAxon() { return std::pair<double, int>(0.0, 0); }

    virtual void addAxon(double earlierTime, int axonIdentifier) {};

    virtual void addAxon(int axonIdentifier) {};
    bool branch(){return m_branchSampler(m_generator);}
};


class uniformLengthNoWaitingTimeSampler : public ProcessSampler {
    std::uniform_real_distribution<double> m_lengthSampler;

public:
    uniformLengthNoWaitingTimeSampler(double low, double high);

    double sampleLength() override;
};

class constantLengthNoWaitingTimeSampler : public ProcessSampler {
    double m_length;
public:
    explicit constantLengthNoWaitingTimeSampler(double length);

    double sampleLength() override;
};

struct Comparator {
    bool operator()(const std::pair<double, int> &a, const std::pair<double, int> &b) {
        return a.first < b.first;
    }
};

class biasedRandomWalk : public ProcessSampler {
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, Comparator> m_waitingTimeQueue;
    std::uniform_real_distribution<double> m_waitingTimeSampler;
public:
    explicit biasedRandomWalk();

    double sampleLength() override;

    std::pair<double, int> getNextAxon() override;

    void addAxon(double earlierTime, int axonIdentifier) override;

    void addAxon(int axonIdentifier) override;
};

#endif //TUMORSIMULATION_PROCESSSAMPLER_H
