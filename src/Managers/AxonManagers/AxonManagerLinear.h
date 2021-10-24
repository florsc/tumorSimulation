//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONMANAGERLINEAR_H
#define TUMORSIMULATION_AXONMANAGERLINEAR_H

#include "AxonManager.h"

class AxonManagerLinear : public AxonManager {
    std::list<AxonHandle> m_activeAxons;
    std::list<AxonHandle>::iterator m_currentAxon;
public:
    AxonManagerLinear() : m_activeAxons(), m_currentAxon(m_activeAxons.begin()) {}

    void addAxon(AxonHandle axon);

    AxonHandle getNextAxon();

};


#endif //TUMORSIMULATION_AXONMANAGERLINEAR_H
