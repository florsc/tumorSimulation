
//
// Created by florian on 10/12/21.
//
#include "AxonFactory.h"

#include <utility>
#include "../../SimulationSetUp/ParameterStruct.h"
#include "../../Managers/ConstraintManager.h"
#include "../../Managers/SimulationManager.h"
#include "../../Managers/TargetManager.h"
#include "../AxonTypes/BaseAxon/BaseAxon.h"
#include "../../ExteriorLimits/ExteriorLimit.h"

void AxonFactory::setUpFactory(SimulationManagerHandle simulationManager) {
    m_baseAxonParameters.simulationManager = std::move(simulationManager);
    if (auto simulationManager = m_baseAxonParameters.simulationManager.lock()) {
        m_baseAxonParameters.targetManager = simulationManager->getTargetManager();
        m_baseAxonParameters.constraintManager = simulationManager->getConstraintManager();
    }
}

void AxonFactory::setUpRoot(const AxonHandle &axon, const WeakAxonHandle &rootAxon) const {
    if (rootAxon.lock()) {
        axon->setUpRootAxon(rootAxon);
    } else {
        axon->setUpRootAxon(axon);
    }
}

AxonFactory::AxonFactory(AxonSetUpParametersHandle axonSetUpParameters) : m_baseAxonParameters(axonSetUpParameters) {
}

