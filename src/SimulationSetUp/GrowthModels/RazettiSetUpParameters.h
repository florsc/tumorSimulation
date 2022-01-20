//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_RAZETTISETUPPARAMETERS_H
#define TUMORSIMULATION_RAZETTISETUPPARAMETERS_H

#include "AxonSetUpParameters.h"
#include "../../util/Samplers.h"

struct RazettiSetUpParameters : public AxonSetUpParameters {
    int numberOfGrowthStepsEachStep;
    int numberOfRetractions;
    int maxNumberOfConstraintEncountersEachSubstep;
    double beta;
    double maxAngleFraction;
    SamplerHandle startAngleSampler = std::make_shared<UniformDoubleSampler>(0, 2 * M_PI);
    SamplerHandle lengthSampler = std::make_shared<LogNormalSampler>(log(0.2), 1);

    RazettiSetUpParameters();
};

#endif //TUMORSIMULATION_RAZETTISETUPPARAMETERS_H
