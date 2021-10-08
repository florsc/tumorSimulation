//
// Created by florian on 9/30/21.
//

#ifndef TUMORSIMULATION_AXONMANAGER_H
#define TUMORSIMULATION_AXONMANAGER_H


#include "Axon.h"
#include "ParameterStruct.h"
#include <vector>
#include <memory>

class Axon;

class AxonManager {
protected:
    std::vector<std::shared_ptr<Axon>> m_allAxons;
public:
    virtual std::shared_ptr<Axon> getNextAxon() = 0;

    virtual void addAxon(std::shared_ptr<Axon> axon) = 0;

    virtual std::vector<std::shared_ptr<Axon>> getAllAxons() { return m_allAxons; }

};

class AxonManagerNoWaitingTime : public AxonManager {
    std::list<std::shared_ptr<Axon>> m_activeAxons;
    std::list<std::shared_ptr<Axon>>::iterator m_currentAxon;
public:
    AxonManagerNoWaitingTime() : m_activeAxons(), m_currentAxon(m_activeAxons.begin()) {}

    void addAxon(std::shared_ptr<Axon> axon) {
        m_allAxons.push_back(axon);
        m_activeAxons.push_back(axon);
    }

    std::shared_ptr<Axon> getNextAxon();

};

struct Comparator {
    bool
    operator()(const std::pair<double, std::shared_ptr<Axon>> &a, const std::pair<double, std::shared_ptr<Axon>> &b) {
        return a.first > b.first;
    }
};

class AxonManagerWaitingTime : public AxonManager {
    double m_currentTime{0};
    std::priority_queue<std::pair<double, std::shared_ptr<Axon>>, std::vector<std::pair<double, std::shared_ptr<Axon>>>, Comparator> m_waitingTimeQueue;
public:
    std::shared_ptr<Axon> getNextAxon();

    void addAxon(std::shared_ptr<Axon> axon);
};

#endif //TUMORSIMULATION_AXONMANAGER_H
