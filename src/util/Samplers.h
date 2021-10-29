//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_SAMPLERS_H
#define TUMORSIMULATION_SAMPLERS_H

#include <random>
#include "TypeDefs.h"

class Samplers {
protected:
    Samplers();

    GeneratorHandle m_generator;
public:
    virtual double sample() = 0;

};

class UniformDoubleSampler : public Samplers {
    std::uniform_real_distribution<double> m_dist;
public:
    UniformDoubleSampler(double low, double high) : Samplers(), m_dist(std::uniform_real_distribution(low, high)) {}

    double sample() override { return m_dist(*m_generator); }
};


class ConstantValueSampler : public Samplers {
    double m_constantValue;
public:
    ConstantValueSampler(double constantValue) : m_constantValue(constantValue) {}

    double sample() override { return m_constantValue; }
};


//For tests only

class DoubleSamplerForTests : public Samplers {
    std::vector<double> m_values;
    std::vector<double>::iterator m_currentValue;
public:
    DoubleSamplerForTests(std::initializer_list<double> values) : m_values(values),m_currentValue(m_values.begin()) {}

    double sample() override { return *(m_currentValue++); }
};


#endif //TUMORSIMULATION_SAMPLERS_H
