//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_RAZETTIAXONPARAMETERS_H
#define TUMORSIMULATION_RAZETTIAXONPARAMETERS_H

#include "../../../SimulationSetUp/GrowthModels/RazettiSetUpParameters.h"
#include "../BaseAxon/BaseAxonParameters.h"

struct RazettiAxonParameters {
    const int numberOfSubstepsEachStep;
    const int maxNumberOfConstraintEncountersEachSubstep;
    const int numberOfRetractions;
    const double alpha;
    const double beta;
    SamplerHandle lengthSampler;

    RazettiAxonParameters() : numberOfSubstepsEachStep(RazettiSetUpParameters::numberOfGrowthStepsEachStep),
                              numberOfRetractions(RazettiSetUpParameters::numberOfRetractions),
                              maxNumberOfConstraintEncountersEachSubstep(
                                      RazettiSetUpParameters::maxNumberOfConstraintEncountersEachSubstep),
                              alpha(RazettiSetUpParameters::alpha),
                              beta(RazettiSetUpParameters::beta),
                              lengthSampler(razettiSetUpParameters.getLengthSampler()) {}
};

#endif //TUMORSIMULATION_RAZETTIAXONPARAMETERS_H
