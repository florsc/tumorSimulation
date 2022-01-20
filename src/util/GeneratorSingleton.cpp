//
// Created by florian on 1/10/22.
//
#include "GeneratorSingleton.h"
#include <fstream>

GeneratorSingleton::GeneratorSingleton(){
        m_generator = std::make_shared<Generator>(m_seed);
std::ofstream seedFile;
seedFile.open("seeds.txt", std::ios_base::app);
seedFile << m_seed << "\n";
seedFile.close();
}

GeneratorSingletonHandle GeneratorSingleton::getInstance() {
    if(!m_instance){
        m_instance = std::make_shared<GeneratorSingleton>();
    }
    return m_instance;
}
GeneratorSingletonHandle GeneratorSingleton::m_instance = GeneratorSingletonHandle (nullptr);