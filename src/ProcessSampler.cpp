//
// Created by florian on 9/23/21.
//

#include "ProcessSampler.h"
#include <iostream>
ProcessSampler::ProcessSampler(bool sampleWaitingTime, std::mt19937 generator) : m_sampleWaitingTime(sampleWaitingTime),
                                                                                 m_generator(generator) {

}


uniformLengthNoWaitingTimeSampler::uniformLengthNoWaitingTimeSampler(double low, double high) : m_lengthSampler(
        std::uniform_real_distribution<double>(low, high)), ProcessSampler(false) {

}

double uniformLengthNoWaitingTimeSampler::sampleLength() {
    return m_lengthSampler(m_generator);
}

constantLengthNoWaitingTimeSampler::constantLengthNoWaitingTimeSampler(double length) : m_length(length) {

}

double constantLengthNoWaitingTimeSampler::sampleLength() {
    return m_length;
}

void biasedRandomWalk::addAxon(double earlierTime, int axonIdentifier) {
    double tmp = m_waitingTimeSampler(m_generator);
    m_waitingTimeQueue.push(std::make_pair<double, int>(earlierTime-tmp, std::move(axonIdentifier)));
}

biasedRandomWalk::biasedRandomWalk(): m_waitingTimeSampler(
        std::uniform_real_distribution<double>(0,1)), ProcessSampler(true) {
}

std::pair<double,int> biasedRandomWalk::getNextAxon() {
    auto tmp = m_waitingTimeQueue.top();
    m_waitingTimeQueue.pop();
    return tmp;
}

double biasedRandomWalk::sampleLength() {
    return 4.0;
}

void biasedRandomWalk::addAxon(int axonIdentifier) {
addAxon(0.0,axonIdentifier);}
