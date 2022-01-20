//
// Created by florian on 10/15/21.
//

#include "AxonOrderSampledWaitingTimeData.h"

AxonOrderSampledWaitingTimeData::AxonOrderSampledWaitingTimeData() {

    waitingTimeSampler = std::make_shared<UniformDoubleSampler>(0.1, 1);
    double maximumTime = 30.0; //simulation stops after this time
}