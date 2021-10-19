//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONMANAGERNOWAITINGTIME_H
#define TUMORSIMULATION_AXONMANAGERNOWAITINGTIME_H

#include "AxonManager.h"

class AxonManagerNoWaitingTime : public AxonManager {
    std::list<AxonHandle> m_activeAxons;
    std::list<AxonHandle>::iterator m_currentAxon;
public:
    AxonManagerNoWaitingTime() : m_activeAxons(), m_currentAxon(m_activeAxons.begin()) {}

    void addAxon(AxonHandle axon);

    AxonHandle getNextAxon();

};


#endif //TUMORSIMULATION_AXONMANAGERNOWAITINGTIME_H
