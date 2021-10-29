//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_RAZETTISETUPPARAMETERS_H
#define TUMORSIMULATION_RAZETTISETUPPARAMETERS_H

#include "AxonSetUpParameters.h"
#include "../../util/Samplers.h"

struct RazettiSetUpParameters {
    static constexpr int numberOfGrowthStepsEachStep = 6;
    static constexpr int numberOfRetractions = 2;
    static constexpr int maxNumberOfConstraintEncountersEachSubstep = 2;
    static constexpr double alpha = 0.5;
    static constexpr double beta = 0;
    static const SamplerHandle lengthSampler;
};

#endif //TUMORSIMULATION_RAZETTISETUPPARAMETERS_H
