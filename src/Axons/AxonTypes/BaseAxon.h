//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_BASEAXON_H
#define TUMORSIMULATION_BASEAXON_H


#include <vector>
#include "../../util/TypeDefs.h"
#include "../../util/EuclideanVector.h"

class ConstraintManager;

class EuclideanVector;

class BaseAxon {
protected:
    PositionVector m_tipPositions;
    GeneratorHandle m_generator;
    AxonVector childAxons;
    ConstraintManagerHandle m_constraintHandler;
    int m_maxConstraintsEachGrowthStep;
    SimulationManagerHandle m_simulationManager;
    int m_identifier;
    bool m_active{true};
    bool m_isAlive{true};

    static int m_currentIdentifier;

protected:

    BaseAxon(const EuclideanVector& startPosition, int maxConstraintsEachGrowthStep, ConstraintManagerHandle constraintHandler,
             SimulationManagerHandle simulationManager);

    BaseAxon(const EuclideanVector& startPosition, const EuclideanVector& nextPosition, int maxConstraintsEachGrowthStep,
             ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManager);

public:

    virtual void killAxon();

    [[nodiscard]] PositionVector getTipPositions() const { return m_tipPositions; }

    virtual void stopAxon() { m_active = false; }

    [[nodiscard]] bool hasId(const int id) const { return m_identifier == id; }

    [[nodiscard]] bool isActive() const { return m_active; }

    [[nodiscard]] bool isAlive() const {
        return m_isAlive;
    }

public:

    virtual void grow() = 0;

};


#endif //TUMORSIMULATION_BASEAXON_H
