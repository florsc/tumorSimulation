//
// Created by florian on 10/23/21.
//

#ifndef TUMORSIMULATION_SIMULATIONEXCEPTION_H
#define TUMORSIMULATION_SIMULATIONEXCEPTION_H


#include <exception>
#include <string>

class SimulationException : public std::exception {
    std::string m_message;
public:
    SimulationException(const char *message) : m_message(message) {}

    const char *what() const noexcept override{ return m_message.c_str(); }

};


#endif //TUMORSIMULATION_SIMULATIONEXCEPTION_H
