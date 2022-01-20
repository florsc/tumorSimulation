//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_RAZETTIAXONPARAMETERS_H
#define TUMORSIMULATION_RAZETTIAXONPARAMETERS_H

#include "../../../SimulationSetUp/GrowthModels/RazettiSetUpParameters.h"
#include "../BaseAxon/BaseAxonParameters.h"
#include "../../../SimulationSetUp/ParameterStruct.h"

struct RazettiAxonParameters {
    const int numberOfSubstepsEachStep;
    const int maxNumberOfConstraintEncountersEachSubstep;
    const int numberOfRetractions;
    const double beta;
    const double maxAngleFraction;
    SamplerHandle lengthSampler;

    RazettiAxonParameters(RazettiSetUpParametersHandle razettiSetUpParameters) : numberOfSubstepsEachStep(razettiSetUpParameters->numberOfGrowthStepsEachStep),
                              numberOfRetractions(razettiSetUpParameters->numberOfRetractions),
                              maxNumberOfConstraintEncountersEachSubstep(
                                      razettiSetUpParameters->maxNumberOfConstraintEncountersEachSubstep),
                              beta(razettiSetUpParameters->beta),maxAngleFraction(razettiSetUpParameters->maxAngleFraction),
                              lengthSampler(razettiSetUpParameters->lengthSampler) {}
};

#endif //TUMORSIMULATION_RAZETTIAXONPARAMETERS_H
