//
// Created by florian on 10/18/21.
//

#include "RandomDirection.h"
#include "../../Axons/Factories/RandomDirectionFactory.h"

AxonFactoryHandle RandomDirection::makeAxonFactory(SimulationManagerHandle simulationManager) {
    return AxonFactoryHandle(
            new RandomDirectionFactory(maxNumberOfConstraintEncounters, lengthSampler, simulationManager, angleBackwardThreshold));
}
