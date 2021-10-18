//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_GROWTHMODEL_H
#define TUMORSIMULATION_GROWTHMODEL_H

#include "../../util/TypeDefs.h"

struct GrowthModel{
public:
    GrowthModel(){}
    virtual AxonFactoryHandle makeAxonFactory(SimulationManagerHandle simulationManager)=0;
};
#endif //TUMORSIMULATION_GROWTHMODEL_H
