//
// Created by florian on 9/22/21.
//

#ifndef TUMORSIMULATION_SIMULATIONMANAGER_H
#define TUMORSIMULATION_SIMULATIONMANAGER_H


#include <queue>
#include <list>
#include "../util/TypeDefs.h"

class ParameterStruct;

class AxonManager;


class SimulationManager {
    AxonManagerHandle m_axonManager;
    AxonFactoryHandle m_axonFactory;

public:
    explicit SimulationManager();

    void setUp(SimulationManagerHandle simulationManager);

    static std::list<EuclideanVector>
    createPossibleStartPositions(const EuclideanVector &c1, const EuclideanVector &c2, double minDistance);

    void run();

    std::vector<std::vector<std::vector<double>>> getAxonPositions();

    void addAxon(const EuclideanVector &startPosition);

    void removeAxon(const int id);

    void addStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition);

    void addAxon(AxonHandle axon);

    ~SimulationManager();

};


#endif //TUMORSIMULATION_SIMULATIONMANAGER_H
