//
// Created by florian on 9/9/21.
//
#include <memory>
#include <vector>
#include "ConstraintHandler.h"
#include <chrono>
#include "EuclideanVector.h"
#include "ProcessSampler.h"
#include "AxonManager.h"
#include <random>
#include <queue>
#include "ProcessSampler.h"

#ifndef TUMORSIMULATION_AXON_H
#define TUMORSIMULATION_AXON_H

class ProcessSampler;
class AxonManager;

class Axon {
    using PositionList = std::vector<EuclideanVector>;
    using AngleList = std::vector<std::vector<double>>;
    std::mt19937 generator{static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::uniform_real_distribution<double> sampler{0.0, 1.0};
    PositionList tipPositions;
    AngleList angles;
    std::shared_ptr<ConstraintHandler> m_constraintHandler;
    std::shared_ptr<ProcessSampler> m_processSampler;
    AxonManager& m_AxonManager;
    int m_identifier;
    std::vector<std::shared_ptr<Axon>> m_childAxons;
    bool m_active{true};
    int m_constraintCounter{0};
public:
    static bool
    checkForBackwardGrowth(double previousAz, double previousEl, double newAz, double newEl, double threshold);
    [[nodiscard]] int getIdentifier() const{return m_identifier;}
    void createNewBranch();

    static std::vector<EuclideanVector> createCenters(EuclideanVector start, EuclideanVector end);

    PositionList getTipPositions() { return tipPositions; }

    std::shared_ptr<ConstraintHandler> occupiedSpaceCenters;

    Axon(int identifier, EuclideanVector startPosition, std::shared_ptr<ConstraintHandler> constraintHandler, std::shared_ptr<ProcessSampler> processSampler, AxonManager& axonManager);

    Axon(int identifier, EuclideanVector startPosition,  EuclideanVector nextPosition, std::shared_ptr<ConstraintHandler> constraintHandler, std::shared_ptr<ProcessSampler> processSampler, AxonManager& axonManager);

    void growthStep();

    [[nodiscard]] bool isActive() const {return m_active;}

    void stopAxon(){m_active = false;}

    static double angleDifferenceCalculator(double a1, double a2);
};


#endif //TUMORSIMULATION_AXON_H
