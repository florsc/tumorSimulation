//
// Created by florian on 9/30/21.
//

#ifndef TUMORSIMULATION_AXONMANAGER_H
#define TUMORSIMULATION_AXONMANAGER_H


#include "../SimulationSetUp/ParameterStruct.h"
#include <vector>
#include <memory>
#include <queue>
#include "../util/TypeDefs.h"

class Axon;

class AxonManager {
protected:
    AxonVector m_allAxons;
public:
    virtual AxonHandle getNextAxon() = 0;

    virtual void addAxon(AxonHandle axon) = 0;

    AxonVector getAllAxons() { return m_allAxons; }

};

class AxonManagerNoWaitingTime : public AxonManager {
    std::list<AxonHandle> m_activeAxons;
    std::list<AxonHandle>::iterator m_currentAxon;
public:
    AxonManagerNoWaitingTime() : m_activeAxons(), m_currentAxon(m_activeAxons.begin()) {}

    void addAxon(AxonHandle axon);

    AxonHandle getNextAxon();

};

struct Comparator {
    bool
    operator()(const std::pair<double, AxonHandle> &a, const std::pair<double, AxonHandle> &b) {
        return a.first > b.first;
    }
};

class AxonManagerWaitingTime : public AxonManager {
    double m_currentTime{0};
    std::priority_queue<std::pair<double, AxonHandle>, std::vector<std::pair<double, AxonHandle>>, Comparator> m_waitingTimeQueue;
public:
    AxonHandle getNextAxon();

    void addAxon(AxonHandle axon);
};

#endif //TUMORSIMULATION_AXONMANAGER_H
