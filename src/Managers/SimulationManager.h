//
// Created by florian on 9/22/21.
//

#ifndef TUMORSIMULATION_SIMULATIONMANAGER_H
#define TUMORSIMULATION_SIMULATIONMANAGER_H


#include <queue>
#include <list>
#include "../util/TypeDefs.h"
#include "../SimulationSetUp/GrowthModels/AxonSetUpParameters.h"

class ParameterStruct;

class AxonManager;


class SimulationManager {
    AxonManagerHandle m_axonManager;
    AxonFactoryHandle m_axonFactory;

public:

    void setUp(SimulationManagerHandle simulationManager, double branchingProbability = AxonSetUpParameters::branchingProbability);

    static PositionList
    createPossibleStartPositions(const EuclideanVector &c1, const EuclideanVector &c2, double minDistance);

    void run();

    [[nodiscard]] std::vector<std::vector<std::vector<double>>> getAxonPositions() const;

    void removeAxon(int id);

    AxonHandle addAxon(const EuclideanVector &startPosition, int constraintsEncountered = 0,
                       WeakAxonHandle rootAxon = WeakAxonHandle());

    AxonHandle addStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                              int constraintsEncountered = 0, WeakAxonHandle rootAxon = WeakAxonHandle());

    void addAxon(AxonHandle axon);

    int getNumberOfTargetReached();
double getNumberOfAxons();
    //test related
    friend class AxonTest;

    double getAxonLength();
};


#endif //TUMORSIMULATION_SIMULATIONMANAGER_H
