
//
// Created by florian on 10/12/21.
//
#include "AxonFactory.h"
#include "../../SimulationSetUp/ParameterStruct.h"
#include "../../Managers/ConstraintManager.h"

AxonFactory::AxonFactory(SimulationManagerHandle simulationManager) : m_constraintManager(
        new ConstraintManager(parameters.exteriorLimit, parameters.minDistance)),
                                                                      m_simulationManager(simulationManager) {}

