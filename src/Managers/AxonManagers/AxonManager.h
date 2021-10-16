//
// Created by florian on 9/30/21.
//

#ifndef TUMORSIMULATION_AXONMANAGER_H
#define TUMORSIMULATION_AXONMANAGER_H


#include <vector>
#include <memory>
#include <queue>
#include <list>
#include "../../util/TypeDefs.h"

class Axon;

class AxonManager {
protected:
    AxonVector m_allAxons;
public:
    virtual AxonHandle getNextAxon() = 0;

    virtual void addAxon(AxonHandle axon) = 0;

    AxonVector getAllAxons() { return m_allAxons; }

};


#endif //TUMORSIMULATION_AXONMANAGER_H
