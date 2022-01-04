//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONAXONPARAMETERS_H
#define TUMORSIMULATION_RANDOMDIRECTIONAXONPARAMETERS_H

#include "../../../SimulationSetUp/GrowthModels/RandomDirectionSetUpParameters.h"
#include "../BaseAxon/BaseAxonParameters.h"

struct RandomDirectionAxonParameters {
    double angleBackwardThreshold;
    SamplerHandle lengthSampler;

    RandomDirectionAxonParameters() :
            angleBackwardThreshold(RandomDirectionSetUpParameters::angleBackwardThreshold),
            lengthSampler(randomDirectionSetUpParameters.getLengthSampler()) {
    }
};

#endif //TUMORSIMULATION_RANDOMDIRECTIONAXONPARAMETERS_H
