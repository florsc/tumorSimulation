//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_BASEAXON_H
#define TUMORSIMULATION_BASEAXON_H


#include <vector>
#include "../../util/TypeDefs.h"

class ConstraintManager;

class EuclideanVector;

class BaseAxon {
protected:
    PositionVector m_tipPositions;
    AxonVector childAxons;
    ConstraintManagerHandle m_constraintHandler;
    SimulationManagerHandle m_simulationManager;
    int m_identifier;
    bool m_active{true};
    bool m_isAlive{true};

    static int m_currentIdentifier;

protected:

    BaseAxon(EuclideanVector startPosition, ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManager);

    BaseAxon(EuclideanVector startPosition, EuclideanVector nextPosition,
             ConstraintManagerHandle constraintHandler, SimulationManagerHandle simulationManager);

public:
    virtual void stopAxon();


    virtual void killAxon();;
    [[nodiscard]] virtual bool isActive() const;

    virtual void createNewBranch(EuclideanVector startPosition);

    virtual void grow() = 0;

    PositionVector getTipPositions();

    bool hasId(const int id) {return m_identifier == id;}


};


#endif //TUMORSIMULATION_BASEAXON_H
