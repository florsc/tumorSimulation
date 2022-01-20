//
// Created by florian on 10/20/21.
//
#include <iostream>
#include "RazettiSetUpParameters.h"
#include <cmath>

//oriented on the growth from the razetti paper
// substeps at each timestep
// retraction in a timestep if constraint is encountered
// relative angle is sampled by a shifted and scaled beta distribution
// (centered at zero, symmetric, between +-maxAngleFraction*Pi, large beta -> probability mass more centered)
// perpendicular direction is randomly sampled

RazettiSetUpParameters::RazettiSetUpParameters() : AxonSetUpParameters() {
    numberOfGrowthStepsEachStep = 5; //substeps each timestep
    numberOfRetractions = 2; //retractions in a timestep when constraint is encountered
    maxNumberOfConstraintEncountersEachSubstep = 2; //maximum constraints before timestep is ended
    beta = 12; //distribution parameter
    maxAngleFraction = 0.75; //fraction of right angle possible for sampling
    startAngleSampler = std::make_shared<UniformDoubleSampler>(0, 2 * M_PI); //sampler for starting angle, currently set in simulationLibrary.cpp
    lengthSampler = std::make_shared<LogNormalSampler>(log(0.2), 1); //samples length for each substep
}