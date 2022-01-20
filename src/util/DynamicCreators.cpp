//
// Created by florian on 1/17/22.
//

#include "DynamicCreators.h"
#include "../Axons/Factories/RandomDirectionFactory.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../Managers/AxonManagers/AxonManagerWaitingTime.h"
#include "../Managers/AxonManagers/AxonManagerLinear.h"
#include "../Targets/SphericalTarget.h"
#include "../SimulationSetUp/TargetSetUp/SphericalTargetSetUpParameters.h"

AxonFactoryHandle createAxonFactory(AxonSetUpParametersHandle axonSetUpParameters) {
    if (auto randomDirectionSetUpParameters = std::dynamic_pointer_cast<RandomDirectionSetUpParameters>(
            axonSetUpParameters)) {
        return std::make_shared<RandomDirectionFactory>(randomDirectionSetUpParameters);
    } else if (auto razettiSetUpParameters = std::dynamic_pointer_cast<RazettiSetUpParameters>(
            axonSetUpParameters)) {
        return std::make_shared<RazettiFactory>(razettiSetUpParameters);
    } else {
        throw SimulationException("Parameters for axon set up are not known.");
    }
}

AxonManagerHandle createAxonManager(AxonOrderDataHandle axonOrderData) {
    if (auto axonOrderSampledWaitingTimeData = std::dynamic_pointer_cast<AxonOrderSampledWaitingTimeData>(
            axonOrderData)) {
        return std::make_shared<AxonManagerWaitingTime>(axonOrderSampledWaitingTimeData);
    } else if (auto axonOrderLinearData = std::dynamic_pointer_cast<AxonOrderLinearData>(axonOrderData)) {
        return std::make_shared<AxonManagerLinear>(axonOrderLinearData);
    } else {
        throw SimulationException("Parameters for axon order are not known.");
    }
}

TargetHandle createTarget(TargetSetUpParametersHandle targetSetUpParameters) {
    if (auto sphericalTargetSetUpParameters = std::dynamic_pointer_cast<SphericalTargetSetUpParameters>(
            targetSetUpParameters)) {
        return std::make_shared<SphericalTarget>(sphericalTargetSetUpParameters);
    } else {
        throw SimulationException("Parameters for target are not known.");
    }
}