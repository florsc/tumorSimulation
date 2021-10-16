//
// Created by florian on 10/15/21.
//

#include "Razetti.h"
#include "../../Axons/Factories/RazettiFactory.h"

AxonFactoryHandle Razetti::makeAxonFactory() {
    return AxonFactoryHandle (new RazettiFactory(6, 2, 100, 10, 0, 1));
}
