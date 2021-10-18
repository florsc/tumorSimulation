//
// Created by florian on 9/30/21.
//

#ifndef TUMORSIMULATION_AXONMANAGER_H
#define TUMORSIMULATION_AXONMANAGER_H


#include <vector>
#include <memory>
#include <queue>
#include <list>
#include <algorithm>
#include "../../util/TypeDefs.h"

class Axon;

class AxonManager {
protected:
    AxonList m_allAxons;
public:
    virtual AxonHandle getNextAxon() = 0;

    virtual void addAxon(AxonHandle axon) = 0;

    void removeAxon(int id);

    AxonList getAllAxons() {
        return m_allAxons; }

};


#endif //TUMORSIMULATION_AXONMANAGER_H
