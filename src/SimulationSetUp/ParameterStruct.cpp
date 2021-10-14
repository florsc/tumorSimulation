//
// Created by florian on 9/29/21.
//

#include "ParameterStruct.h"
#include "../Sampler.h"

ParameterStruct::ParameterStruct() : sampler(new biasedRandomWalk()) {

}

ParameterStruct parameters;