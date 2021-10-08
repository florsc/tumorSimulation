//
// Created by florian on 9/9/21.
//

#ifndef TUMORSIMULATION_AXON_H
#define TUMORSIMULATION_AXON_H

#include "ParameterStruct.h"
#include <memory>
#include <vector>
#include "ConstraintHandler.h"
#include <chrono>
#include "EuclideanVector.h"
#include "Sampler.h"
#include "SimulationManager.h"
#include <random>
#include <queue>

class Sampler;

class SimulationManager;

class Axon {
    using PositionList = std::vector<EuclideanVector>;
    PositionList m_tipPositions;
    std::shared_ptr<ConstraintHandler> m_constraintHandler;
    SimulationManager &m_AxonManager;
    int m_identifier;
    bool m_active{true};
    int m_constraintCounter{0};
public:
    [[nodiscard]] int getIdentifier() const { return m_identifier; }

    void createNewBranch();

    static std::vector<EuclideanVector> createCenters(const EuclideanVector &start, const EuclideanVector &end);

    PositionList getTipPositions() { return m_tipPositions; }

    Axon(int identifier, EuclideanVector startPosition, std::shared_ptr<ConstraintHandler> constraintHandler,
         SimulationManager &axonManager);

    Axon(int identifier, EuclideanVector startPosition, EuclideanVector nextPosition,
         std::shared_ptr<ConstraintHandler> constraintHandler, SimulationManager &axonManager);

    void growthStep();

    bool isActive() const;

    void stopAxon() { m_active = false; }

    EuclideanVector sampleVector();

    bool checkForBackwardGrowth(const EuclideanVector &oldVector, const EuclideanVector &newVector, double threshold);

    ~Axon(){std::cout<<"Axon destructed"<<std::endl;}
};


#endif //TUMORSIMULATION_AXON_H
