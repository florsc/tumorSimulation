//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONMANAGERWAITINGTIME_H
#define TUMORSIMULATION_AXONMANAGERWAITINGTIME_H


#include "AxonManager.h"

class AxonManagerWaitingTime : public AxonManager {

    struct Comparator {
        bool
        operator()(const std::pair<double, AxonHandle> &a, const std::pair<double, AxonHandle> &b) {
            return a.first > b.first;
        }
    };

    SamplerHandle m_waitingTimeSampler;
    double m_currentTime{0};
    std::priority_queue<std::pair<double, AxonHandle>, std::vector<std::pair<double, AxonHandle>>, Comparator> m_waitingTimeQueue;
    double m_maximumWaitingTime;
public:
    explicit AxonManagerWaitingTime(SamplerHandle &sampler, double maximumWaitingTime);

    AxonHandle getNextAxon();

    void addAxon(AxonHandle axon);
};


#endif //TUMORSIMULATION_AXONMANAGERWAITINGTIME_H
