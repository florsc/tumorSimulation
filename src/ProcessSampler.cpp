//
// Created by florian on 9/23/21.
//

#include "LengthSampler.h"

uniformLengthSampler::uniformLengthSampler(double low, double high):sampler(    std::uniform_real_distribution<double>(low, high)){

}

double uniformLengthSampler::sample() {
    return sampler(generator);
}

constantLengthSampler::constantLengthSampler(double length):m_length(length) {

}

double constantLengthSampler::sample() {
    return m_length;
}
