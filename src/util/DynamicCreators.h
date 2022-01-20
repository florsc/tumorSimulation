//
// Created by florian on 1/17/22.
//

#ifndef TUMORSIMULATION_DYNAMICCREATORS_H
#define TUMORSIMULATION_DYNAMICCREATORS_H

#include "TypeDefs.h"

AxonFactoryHandle createAxonFactory(AxonSetUpParametersHandle axonSetUpParameters);

AxonManagerHandle createAxonManager(AxonOrderDataHandle axonOrderData);

TargetHandle createTarget(TargetSetUpParametersHandle);

#endif //TUMORSIMULATION_DYNAMICCREATORS_H
