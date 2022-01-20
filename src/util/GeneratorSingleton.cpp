//
// Created by florian on 1/10/22.
//
#include "GeneratorSingleton.h"
#include <fstream>

GeneratorSingleton::GeneratorSingleton() {
    m_generator = std::make_shared<Generator>(m_seed);
    std::ofstream seedFile;
    seedFile.open("../created_data/seeds.txt", std::ios_base::app);
    auto timepoint = std::chrono::system_clock::now();
    std::time_t timepoint_t = std::chrono::system_clock::to_time_t(timepoint);

    char timeStr[100];
    if (std::strftime(timeStr, sizeof(timeStr), "%d/%m/%Y %T: ", std::localtime(&timepoint_t))) {
        seedFile << timeStr;
    }
    seedFile << m_seed << "\n";
    seedFile.close();
}

GeneratorSingletonHandle GeneratorSingleton::getInstance() {
    if (!m_instance) {
        m_instance = std::make_shared<GeneratorSingleton>();
    }
    return m_instance;
}

GeneratorSingletonHandle GeneratorSingleton::m_instance = GeneratorSingletonHandle(nullptr);