//
// Created by florian on 10/15/21.
//

#include "Razetti.h"
#include "../../Axons/Factories/RazettiFactory.h"

AxonFactoryHandle Razetti::makeAxonFactory(SimulationManagerHandle simulationManager) {
    return AxonFactoryHandle (new RazettiFactory(numberOfGrowthStepsEachTimeStep, numberOfRetractions, maxNumberOfConstraintEncounters, alpha, beta, lengthSampler, simulationManager));
}
