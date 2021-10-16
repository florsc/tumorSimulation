//
// Created by florian on 9/29/21.
//

#include "ParameterStruct.h"
#include "../Sampler.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include "GrowthModels/Razetti.h"
#include "AxonOrder/AxonOrderSampledWaitingTime.h"

ParameterStruct::ParameterStruct() : exteriorLimit(new SphericalLimit(30)),
                                     growthModel(new Razetti()),
                                     axonOrder(new AxonOrderSampledWaitingTime()){

}

ParameterStruct parameters;