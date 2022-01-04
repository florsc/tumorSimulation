//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONSETUPPARAMETERS_H
#define TUMORSIMULATION_RANDOMDIRECTIONSETUPPARAMETERS_H


#include "AxonSetUpParameters.h"
#include "../../util/Samplers.h"

struct RandomDirectionSetUpParameters {
    static constexpr double angleBackwardThreshold = 0.7 * M_PI;
    SamplerHandle lengthSampler;
    SamplerHandle getLengthSampler();
};


extern RandomDirectionSetUpParameters randomDirectionSetUpParameters;
#endif //TUMORSIMULATION_RANDOMDIRECTIONSETUPPARAMETERS_H
