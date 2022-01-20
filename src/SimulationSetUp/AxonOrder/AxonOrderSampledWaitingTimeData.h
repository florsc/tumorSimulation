//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONORDERSAMPLEDWAITINGTIMEDATA_H
#define TUMORSIMULATION_AXONORDERSAMPLEDWAITINGTIMEDATA_H

#include "AxonOrderData.h"
#include "../../util/Samplers.h"

struct AxonOrderSampledWaitingTimeData : public AxonOrderData {
    SamplerHandle waitingTimeSampler{new UniformDoubleSampler(0.1, 1)};
    double maximumTime = 30.0;
};


#endif //TUMORSIMULATION_AXONORDERSAMPLEDWAITINGTIMEDATA_H
