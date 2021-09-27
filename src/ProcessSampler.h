//
// Created by florian on 9/23/21.
//

#ifndef TUMORSIMULATION_LENGTHSAMPLER_H
#define TUMORSIMULATION_LENGTHSAMPLER_H


#include <random>
#include <chrono>

class LengthSampler {
public:
    virtual double sampleLength();
};

class uniformLengthSampler: public LengthSampler{
    std::mt19937 generator{static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::uniform_real_distribution<double> sampler;
public:
    uniformLengthSampler(double low, double high);
    double sample();
};

class constantLengthSampler: public LengthSampler{
    double m_length;
public:
    constantLengthSampler(double length);
    double sample();
};

#endif //TUMORSIMULATION_LENGTHSAMPLER_H
