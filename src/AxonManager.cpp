//
// Created by florian on 9/30/21.
//

#include "AxonManager.h"


void AxonManagerWaitingTime::addAxon(std::shared_ptr<Axon> axon){

    double tmp = parameters.sampler->sampleWaitingTime();
    m_waitingTimeQueue.push(std::pair<double, std::shared_ptr<Axon>>(m_currentTime + tmp, axon));
    }

std::shared_ptr<Axon> AxonManagerWaitingTime::getNextAxon() {
    if(m_currentTime>parameters.maximumTime ){return {};}
    auto tmp = m_waitingTimeQueue.top();
    while(!tmp.second->isActive()){
        m_waitingTimeQueue.pop();
        if(m_waitingTimeQueue.empty()){return {};}
        tmp = m_waitingTimeQueue.top();
    }
    m_waitingTimeQueue.pop();
    m_waitingTimeQueue.push(std::pair<double,std::shared_ptr<Axon>>(tmp.first+parameters.sampler->sampleWaitingTime(), tmp.second));
    m_currentTime = tmp.first;
    return tmp.second;}

std::shared_ptr<Axon> AxonManagerNoWaitingTime::getNextAxon() {
    if(++m_currentAxon == m_activeAxons.end()){
        m_currentAxon = m_activeAxons.begin();
    }
    while(!(*m_currentAxon)->isActive()){
        m_currentAxon = m_activeAxons.erase(m_currentAxon);
        if(m_activeAxons.empty()){return {};}
        if(m_currentAxon == m_activeAxons.end()){m_currentAxon=m_activeAxons.begin();}
    }
    return *m_currentAxon;}