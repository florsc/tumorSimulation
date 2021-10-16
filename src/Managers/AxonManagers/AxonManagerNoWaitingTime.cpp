//
// Created by florian on 10/15/21.
//

#include "AxonManagerNoWaitingTime.h"

#include "AxonManager.h"
#include "../../Sampler.h"
#include "../../Axons/AxonTypes/BaseAxon.h"

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
