//
// Created by florian on 10/15/21.
//

#include "AxonOrderSampledWaitingTime.h"
#include "../../Managers/AxonManagers/AxonManagerWaitingTime.h"
#include "../ParameterStruct.h"

AxonManagerHandle AxonOrderSampledWaitingTime::makeAxonManager() {
    return AxonManagerHandle(new AxonManagerWaitingTime(waitingTimeSampler));
}

