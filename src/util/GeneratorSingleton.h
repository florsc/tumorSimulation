//
// Created by florian on 1/10/22.
//

#ifndef TUMORSIMULATION_GENERATORSINGLETON_H
#define TUMORSIMULATION_GENERATORSINGLETON_H

#include <chrono>
#include "TypeDefs.h"

struct GeneratorSingleton{
    static GeneratorSingletonHandle m_instance;
    long long m_seed = std::chrono::system_clock::now().time_since_epoch().count();
    GeneratorSingleton();
public:
    GeneratorHandle m_generator;
    static GeneratorSingletonHandle getInstance();

};
#endif //TUMORSIMULATION_GENERATORSINGLETON_H
