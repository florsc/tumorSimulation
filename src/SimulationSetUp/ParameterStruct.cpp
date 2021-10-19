//
// Created by florian on 9/29/21.
//

#include "ParameterStruct.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include "GrowthModels/Razetti.h"
#include "GrowthModels/RandomDirection.h"
#include "AxonOrder/AxonOrderSampledWaitingTime.h"

ParameterStruct::ParameterStruct() : exteriorLimit(new SphericalLimit(40)),
                                     growthModel(new RandomDirection()),
                                     axonOrder(new AxonOrderSampledWaitingTime()){

}

ParameterStruct parameters;