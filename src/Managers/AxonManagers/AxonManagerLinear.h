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
    AxonManagerLinear(AxonOrderLinearDataHandle axonOrderLinearData)
            : m_activeAxons(), m_currentAxon(m_activeAxons.begin()) {}

    void addAxon(AxonHandle axon) override;

    AxonHandle getNextAxon() override;

};


#endif //TUMORSIMULATION_AXONMANAGERLINEAR_H
