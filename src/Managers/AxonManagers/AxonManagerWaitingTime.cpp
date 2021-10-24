//
// Created by florian on 10/15/21.
//

#include "AxonManagerWaitingTime.h"
#include "../../SimulationSetUp/ParameterStruct.h"

#include "AxonManager.h"
#include "../../Axons/AxonTypes/BaseAxon/BaseAxon.h"
#include "../../util/Samplers.h"

void AxonManagerWaitingTime::addAxon(AxonHandle axon) {
    m_allAxons.push_back(axon);
    double tmp = m_waitingTimeSampler->sample();
    m_waitingTimeQueue.push(std::pair<double, AxonHandle>(m_currentTime + tmp, axon));
}

AxonHandle AxonManagerWaitingTime::getNextAxon() {
    if (m_currentTime > m_maximumWaitingTime) { return {}; }
    auto tmp = m_waitingTimeQueue.top();
    while (!tmp.second->isActive()) {
        m_waitingTimeQueue.pop();
        if (m_waitingTimeQueue.empty()) { return {}; }
        tmp = m_waitingTimeQueue.top();
    }
    m_waitingTimeQueue.pop();
    m_waitingTimeQueue.push(
            std::pair<double, AxonHandle>(tmp.first + m_waitingTimeSampler->sample(), tmp.second));
    m_currentTime = tmp.first;
    return tmp.second;
}

AxonManagerWaitingTime::AxonManagerWaitingTime(SamplerHandle &sampler, double maximumWaitingTime)
        : m_waitingTimeSampler(std::move(sampler)), m_maximumWaitingTime(maximumWaitingTime) {

}
