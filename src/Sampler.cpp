//
// Created by florian on 9/23/21.
//

#include "Sampler.h"
#include <iostream>

/*
Sampler::Sampler(bool waitingTime) :
        m_uniformSampler(std::uniform_real_distribution<double>(0.0, 1.0)), m_normalSampler(
        std::normal_distribution<>(0, 1)), m_processWithWaitingTime(waitingTime) {

}

bool Sampler::branch() {
    return false;
}

std::pair<double, int> Sampler::getNextAxon() { return {}; }


uniformLengthNoWaitingTimeSampler::uniformLengthNoWaitingTimeSampler(double low, double high) : m_lengthSampler(
        std::uniform_real_distribution<double>(low, high)), Sampler(false) {

}

double uniformLengthNoWaitingTimeSampler::sampleLength() {
    return m_lengthSampler(parameters.m_generator);
}

constantLengthNoWaitingTimeSampler::constantLengthNoWaitingTimeSampler(double length) : m_length(length),
                                                                                        Sampler(false) {

}

double constantLengthNoWaitingTimeSampler::sampleLength() {
    return m_length;
}


biasedRandomWalk::biasedRandomWalk() : m_waitingTimeSampler(
        std::uniform_real_distribution<double>(0, 1)), Sampler(true) {
}


double biasedRandomWalk::sampleLength() {
    return 1.0;
}
*/