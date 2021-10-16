//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_SAMPLERS_H
#define TUMORSIMULATION_SAMPLERS_H

#include <random>
#include "../SimulationSetUp/ParameterStruct.h"

class Samplers {
public:
    virtual double sample() = 0;
};

class UniformDoubleSampler : public Samplers{
    std::uniform_real_distribution<double> dist;
public:
    UniformDoubleSampler(double low, double high):dist(std::uniform_real_distribution(low,high)){}
     double sample() override {return dist(parameters.m_generator);}
};



#endif //TUMORSIMULATION_SAMPLERS_H
