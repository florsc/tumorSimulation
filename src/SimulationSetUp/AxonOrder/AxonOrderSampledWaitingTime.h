//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONORDERSAMPLEDWAITINGTIME_H
#define TUMORSIMULATION_AXONORDERSAMPLEDWAITINGTIME_H

#include "AxonOrder.h"
#include "../../util/Samplers.h"

class AxonOrderSampledWaitingTime : public AxonOrder {
    SamplerHandle waitingTimeSampler{new UniformDoubleSampler(0.1, 1)};
    const double maximumTime = 30.0;
public:
    AxonManagerHandle makeAxonManager() override;
};


#endif //TUMORSIMULATION_AXONORDERSAMPLEDWAITINGTIME_H
