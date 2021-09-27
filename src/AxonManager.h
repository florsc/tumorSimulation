//
// Created by florian on 9/22/21.
//

#ifndef TUMORSIMULATION_AXONMANAGER_H
#define TUMORSIMULATION_AXONMANAGER_H


#include <queue>
#include "Axon.h"
#include "ProcessSampler.h"

class AxonManager {
    std::vector<std::shared_ptr<Axon>> m_axons;
    std::priority_queue<std::shared_ptr<Axon>> waitingTimeQueue;
    std::list<EuclideanVector> m_startPositions;
    std::shared_ptr<ConstraintHandler> m_constraintHandler;
    std::shared_ptr<ProcessSampler> m_processSampler;

public:
    AxonManager(int numberOfStartingAxons, EuclideanVector cornerStartingArea1, EuclideanVector cornerStartingArea2,
                std::shared_ptr<ConstraintHandler> constraintHandler, std::shared_ptr<ProcessSampler> processSampler);

    static std::list<EuclideanVector> sampleStartPositions(EuclideanVector c1, EuclideanVector c2);

    void run();

    std::vector<std::vector<std::vector<double>>> getAxonPositions();

    void addAxon(EuclideanVector startPosition);
};


#endif //TUMORSIMULATION_AXONMANAGER_H
