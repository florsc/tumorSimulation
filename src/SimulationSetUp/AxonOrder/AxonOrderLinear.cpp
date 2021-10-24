//
// Created by florian on 10/15/21.
//

#include "AxonOrderLinear.h"
#include "../../Managers/AxonManagers/AxonManagerLinear.h"

AxonManagerHandle AxonOrderLinear::makeAxonManager() {
    return AxonManagerHandle(new AxonManagerLinear());
}
