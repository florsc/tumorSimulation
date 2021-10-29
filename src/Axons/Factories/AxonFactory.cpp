
//
// Created by florian on 10/12/21.
//
#include "AxonFactory.h"

#include <utility>
#include "../../SimulationSetUp/ParameterStruct.h"
#include "../../Managers/ConstraintManager.h"
#include "../../Managers/TargetManager.h"
#include "../AxonTypes/BaseAxon/BaseAxon.h"

void AxonFactory::setUpFactory(SimulationManagerHandle simulationManager) {
    m_baseAxonParameters.simulationManager = std::move(simulationManager);
    m_baseAxonParameters.constraintManager = std::make_shared<ConstraintManager>
            (parameters.exteriorLimit, ParameterStruct::minDistance);
    m_baseAxonParameters.targetManager = std::make_unique<TargetManager>(parameters.targets);
}

void AxonFactory::setUpRoot(const AxonHandle& axon, const WeakAxonHandle& rootAxon) const {
    if (rootAxon.lock()) {
        axon->setUpRootAxon(rootAxon);
    } else {
        axon->setUpRootAxon(axon);
    }
}

