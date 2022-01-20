//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_RAZETTISETUPPARAMETERS_H
#define TUMORSIMULATION_RAZETTISETUPPARAMETERS_H

#include "AxonSetUpParameters.h"
#include "../../util/Samplers.h"

struct RazettiSetUpParameters:public AxonSetUpParameters {
    int numberOfGrowthStepsEachStep = 5;
    int numberOfRetractions = 2;
    int maxNumberOfConstraintEncountersEachSubstep = 2;
    double beta = 1;
    double maxAngleFraction = 0.75;
    SamplerHandle angleSampler = std::make_shared<UniformDoubleSampler>(0,2*M_PI);
    SamplerHandle lengthSampler = std::make_shared<LogNormalSampler>(log(0.2),1);
    int i = 0;
};

extern RazettiSetUpParameters razettiSetUpParameters;
#endif //TUMORSIMULATION_RAZETTISETUPPARAMETERS_H
