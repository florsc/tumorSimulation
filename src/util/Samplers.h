//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_SAMPLERS_H
#define TUMORSIMULATION_SAMPLERS_H

#include <random>
#include "TypeDefs.h"
#include "GeneratorSingleton.h"
#include "SimulationException.h"

class Samplers {
protected:
    Samplers() : m_generator(GeneratorSingleton::getInstance()->m_generator) {}

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
    ConstantValueSampler(double constantValue) : Samplers(),m_constantValue(constantValue) {}

    double sample() override { return m_constantValue; }
};

class LogNormalSampler : public Samplers {
    std::lognormal_distribution<double> m_dist;
public:
    LogNormalSampler(double logMean, double logVariance) : Samplers(),m_dist(logMean,logVariance) {}

    double sample() override { return m_dist(*m_generator); }
};

class FixedValuesSampler : public Samplers {
    std::vector<double> m_values;
    std::vector<double>::iterator m_currentValue;
public:
    FixedValuesSampler(std::initializer_list<double> values) : Samplers(), m_values(values), m_currentValue(m_values.begin()) {}

    double sample() override {
        if(m_currentValue==m_values.end()){
            throw SimulationException("Sampler for fixed values exceeds list of given values.");
        }
        return *(m_currentValue++); }

        void reset(){m_currentValue = m_values.begin();}
};


#endif //TUMORSIMULATION_SAMPLERS_H
