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
    std::pair<double, double> startAngles;
    int m_identifier;
    bool m_active{true};
    bool m_isAlive{true};
    bool m_targetReached{false};
    int m_constraintCounter;
    BaseAxonParameters m_baseAxonParameters;
    int m_numberOfBranches = 0;
    double m_length = 0;

    static int m_currentIdentifier;

protected:

    BaseAxon(const EuclideanVector &startPosition, int id, BaseAxonParameters baseAxonParameters,
             int constraintsEncountered = 0);

    BaseAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition, int id,
             BaseAxonParameters baseAxonParameters, int constraintsEncountered = 0);
    void increaseBranchNumberBase(){if(auto rootAxon = m_rootAxon.lock()){rootAxon->increaseBranchNumber();}}
    void increaseBranchNumber(){m_numberOfBranches++; for(const auto & child:m_childAxons){child->increaseBranchNumber();}}
    virtual bool checkConstraints(const EuclideanVector &startPosition, const EuclideanVector &growthVector) const;
    virtual bool checkConstraintsAndAdd(const EuclideanVector &startPosition, const EuclideanVector &growthVector, int numberOfGrowthTimes);
    void setBranchNumber(int branchNumber){m_numberOfBranches = branchNumber;}

    bool checkIfBranching() const;

    bool createBranchIfPossible(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) ;

    bool checkTargetReached(const EuclideanVector &position);

    void setTargetReached();

    void checkForStopping();

public:

    void setUpRootAxon(WeakAxonHandle rootAxon) { m_rootAxon = std::move(rootAxon); }
    AxonHandle getRootAxon() { return m_rootAxon.lock(); }

    virtual void killAxon();

    virtual void stopAxonBranch();

    virtual void stopAxon();

    [[nodiscard]] PositionVector getTipPositions() const { return m_tipPositions; }

    [[nodiscard]] bool hasId(const int id) const { return m_identifier == id; }
int getId(){return m_identifier;}
    [[nodiscard]] bool isActive() const { return m_active; }

    [[nodiscard]] bool targetIsReached() const { return m_targetReached; }

    [[nodiscard]] bool isAlive() const {
        return m_isAlive;
    }

    double getAxonLength();
    double getBranchLength();
public:

    virtual void grow() = 0;

    //test related
    friend class AxonTest;

    void checkLength();
};


#endif //TUMORSIMULATION_BASEAXON_H
