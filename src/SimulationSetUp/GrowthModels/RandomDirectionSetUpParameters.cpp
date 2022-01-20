//
// Created by florian on 10/20/21.
//
#include "RandomDirectionSetUpParameters.h"

//growths in random direction, growing backward is forbidden
RandomDirectionSetUpParameters::RandomDirectionSetUpParameters() : AxonSetUpParameters() {
    angleBackwardThreshold = 0.7 * M_PI; //angle between previous and current growth which counts as backward growth
    lengthSampler = std::make_shared<ConstantValueSampler>(1);
}