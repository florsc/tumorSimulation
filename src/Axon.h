//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_AXON_H
#define TUMORSIMULATION_AXON_H
/*
#include "SimulationSetUp/ParameterStruct.h"
#include <memory>
#include <vector>
#include "Managers/ConstraintManager.h"
#include <chrono>
#include "util/EuclideanVector.h"
#include "Sampler.h"
#include "Managers/SimulationManager.h"
#include <random>
#include <queue>

class Sampler;

class SimulationManager;

class Axon {
    using PositionList = std::vector<EuclideanVector>;
    PositionList m_tipPositions;
    std::shared_ptr<ConstraintManager> m_constraintHandler;
    SimulationManager &m_simulationManager;
    int m_identifier;
    bool m_active{true};
    int m_constraintCounter{0};
public:
    [[nodiscard]] int getIdentifier() const { return m_identifier; }

    void createNewBranch();

    PositionList getTipPositions() { return m_tipPositions; }

    Axon(int identifier, EuclideanVector startPosition, std::shared_ptr<ConstraintManager> constraintHandler,
         SimulationManager &axonManager);

    Axon(int identifier, EuclideanVector startPosition, EuclideanVector nextPosition,
         std::shared_ptr<ConstraintManager> constraintHandler, SimulationManager &axonManager);

    void growthStep();

    [[nodiscard]] bool isActive() const;

    ~Axon() { std::cout << "Axon destructed" << std::endl; }

    void stopAxon() { m_active = false; }

    EuclideanVector sampleVector();

};
*/
#endif //TUMORSIMULATION_AXON_H
