//
// Created by florian on 10/20/21.
//
#include "RandomDirectionSetUpParameters.h"

SamplerHandle RandomDirectionSetUpParameters::getLengthSampler() {
    lengthSampler = std::make_shared<ConstantValueSampler>(1);
    return lengthSampler;
}
RandomDirectionSetUpParameters randomDirectionSetUpParameters;