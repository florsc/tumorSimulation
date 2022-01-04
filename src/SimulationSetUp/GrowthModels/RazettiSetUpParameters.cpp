//
// Created by florian on 10/20/21.
//
#include <iostream>
#include "RazettiSetUpParameters.h"
#include <cmath>

SamplerHandle RazettiSetUpParameters::getLengthSampler() {
    lengthSampler = std::make_shared<LogNormalSampler>(log(0.2),1);
    return lengthSampler;
}
RazettiSetUpParameters razettiSetUpParameters;