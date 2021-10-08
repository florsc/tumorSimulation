//
// Created by florian on 9/22/21.
//

#ifndef TUMORSIMULATION_SIMULATIONMANAGER_H
#define TUMORSIMULATION_SIMULATIONMANAGER_H


#include <queue>
#include "Axon.h"
#include "Sampler.h"
#include "SimulationManager.h"
#include "AxonManager.h"
class ParameterStruct;

class Axon;
class AxonManager;
class ConstraintHandler;

class SimulationManager {
    std::vector<std::shared_ptr<Axon>> m_axons;
    std::shared_ptr<ConstraintHandler> m_constraintHandler;
    std::shared_ptr<AxonManager> m_axonManager;

public:
    explicit SimulationManager(std::shared_ptr<ConstraintHandler> constraintHandler);

    static std::list<EuclideanVector> sampleStartPositions(const EuclideanVector &c1, const EuclideanVector &c2);

    void run();

    std::vector<std::vector<std::vector<double>>> getAxonPositions();

    void addAxon(const EuclideanVector& startPosition);

    void addAxon(const EuclideanVector& startPosition, const EuclideanVector& direction);

    void addAxon(std::shared_ptr<Axon> axon);

    ~SimulationManager(){std::cout<<"SimulationManager destructed"<<std::endl;}

};


#endif //TUMORSIMULATION_SIMULATIONMANAGER_H
