//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONSETUPPARAMETERS_H
#define TUMORSIMULATION_RANDOMDIRECTIONSETUPPARAMETERS_H


#include "AxonSetUpParameters.h"
#include "../../util/Samplers.h"

struct RandomDirectionSetUpParameters {
    static constexpr double angleBackwardThreshold = 0.7 * M_PI;
    static SamplerHandle lengthSampler;
};


#endif //TUMORSIMULATION_RANDOMDIRECTIONSETUPPARAMETERS_H
