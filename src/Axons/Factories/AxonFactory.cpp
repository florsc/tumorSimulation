
//
// Created by florian on 10/12/21.
//
#include "AxonFactory.h"

#include <utility>
#include "../../SimulationSetUp/ParameterStruct.h"
#include "../../Managers/ConstraintManager.h"
#include "../../Managers/TargetManager.h"
#include "../AxonTypes/BaseAxon/BaseAxon.h"

AxonFactory::AxonFactory() {}

void AxonFactory::setUpFactory(SimulationManagerHandle simulationManager) {
    m_baseAxonParameters.simulationManager = std::move(simulationManager);
    m_baseAxonParameters.constraintManager = std::make_unique<ConstraintManager>
            (parameters.exteriorLimit, parameters.minDistance);
    m_baseAxonParameters.targetManager = std::make_unique<TargetManager>(parameters.targets);
}

void AxonFactory::setUpRoot(AxonHandle axon, WeakAxonHandle rootAxon) {
    if (rootAxon.lock()) {
        axon->setUpRootAxon(rootAxon);
    } else {
        axon->setUpRootAxon(axon);
    }
}

