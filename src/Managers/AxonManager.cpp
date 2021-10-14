//
// Created by florian on 9/30/21.
//

#include "AxonManager.h"
#include "../Sampler.h"
#include "../Axons/AxonTypes/BaseAxon.h"
#include "../Axons/AxonTypes/RazettiAxon.h"


void AxonManagerWaitingTime::addAxon(AxonHandle axon) {
    m_allAxons.push_back(axon);
    double tmp = parameters.sampler->sampleWaitingTime();
    m_waitingTimeQueue.push(std::pair<double, AxonHandle>(m_currentTime + tmp, axon));
}

AxonHandle AxonManagerWaitingTime::getNextAxon() {
    if (m_currentTime > parameters.maximumTime) { return {}; }
    auto tmp = m_waitingTimeQueue.top();
    while (!tmp.second->isActive()) {
        m_waitingTimeQueue.pop();
        if (m_waitingTimeQueue.empty()) { return {}; }
        tmp = m_waitingTimeQueue.top();
    }
    m_waitingTimeQueue.pop();
    m_waitingTimeQueue.push(
            std::pair<double, AxonHandle>(tmp.first + parameters.sampler->sampleWaitingTime(), tmp.second));
    m_currentTime = tmp.first;
    return tmp.second;
}

AxonHandle AxonManagerNoWaitingTime::getNextAxon() {
    if (++m_currentAxon == m_activeAxons.end()) {
        m_currentAxon = m_activeAxons.begin();
    }
    while (!(*m_currentAxon)->isActive()) {
        m_currentAxon = m_activeAxons.erase(m_currentAxon);
        if (m_activeAxons.empty()) { return {}; }
        if (m_currentAxon == m_activeAxons.end()) { m_currentAxon = m_activeAxons.begin(); }
    }
    return *m_currentAxon;
}

void AxonManagerNoWaitingTime::addAxon(AxonHandle axon) {
    m_allAxons.push_back(axon);
    m_activeAxons.push_back(axon);
}
