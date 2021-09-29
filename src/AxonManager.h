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
    std::shared_ptr<ConstraintHandler> m_constraintHandler;
    std::shared_ptr<ProcessSampler> m_processSampler;
    double m_currentTime{0};

public:
    AxonManager(int numberOfStartingAxons, const EuclideanVector& cornerStartingArea1, const EuclideanVector& cornerStartingArea2,
                std::shared_ptr<ConstraintHandler> constraintHandler, std::shared_ptr<ProcessSampler> processSampler);

    static std::list<EuclideanVector> sampleStartPositions(const EuclideanVector& c1, const EuclideanVector& c2);

    void run();

    std::vector<std::vector<std::vector<double>>> getAxonPositions();

    void addAxon(EuclideanVector startPosition);

    void addAxon(EuclideanVector startPosition, EuclideanVector direction);

    void addAxon(std::shared_ptr<Axon> axon);
    int getNumOfAxons(){return m_axons.size();}
};


#endif //TUMORSIMULATION_AXONMANAGER_H
