//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_BASEAXON_H
#define TUMORSIMULATION_BASEAXON_H


#include <utility>
#include <vector>
#include <iostream>
#include "../../../util/TypeDefs.h"
#include "../../../util/EuclideanVector.h"
#include "BaseAxonParameters.h"

class ConstraintManager;

class EuclideanVector;
class AxonTest;

class BaseAxon {
protected:
    PositionVector m_tipPositions;
    GeneratorHandle m_generator;
    AxonVector m_childAxons;
    WeakAxonHandle m_rootAxon;
    int m_identifier;
    bool m_active{true};
    bool m_isAlive{true};
    bool m_targetReached{false};
    int m_constraintCounter;
    BaseAxonParameters m_baseAxonParameters;

    static int m_currentIdentifier;

protected:

    BaseAxon(const EuclideanVector &startPosition, BaseAxonParameters baseAxonParameters,
             int constraintsEncountered = 0);

    BaseAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
             BaseAxonParameters baseAxonParameters, int constraintsEncountered = 0);

    virtual bool checkConstraints(const PositionVector &positions) const;

    bool checkIfBranching() const;

    bool createBranchIfPossible(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) const;

    bool checkTargetReached(const EuclideanVector &position);

    void setTargetReached();

    void checkForStopping();

public:

    void setUpRootAxon(WeakAxonHandle rootAxon) { m_rootAxon = std::move(rootAxon); }

    virtual void killAxon();

    virtual void stopAxonBranch();

    virtual void stopAxon();

    [[nodiscard]] PositionVector getTipPositions() const { return m_tipPositions; }

    [[nodiscard]] bool hasId(const int id) const { return m_identifier == id; }

    [[nodiscard]] bool isActive() const { return m_active; }

    [[nodiscard]] bool targetIsReached() const { return m_targetReached; }

    [[nodiscard]] bool isAlive() const {
        return m_isAlive;
    }

public:

    virtual void grow() = 0;

    //test related
    friend class AxonTest;
};


#endif //TUMORSIMULATION_BASEAXON_H
