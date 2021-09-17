//
// Created by florian on 9/9/21.
//
#include <memory>
#include <vector>
#include "OccupiedSpace.h"
#include <chrono>

#include <random>

#ifndef TUMORSIMULATION_AXON_H
#define TUMORSIMULATION_AXON_H


class Axon {
    std::mt19937 generator{static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::uniform_real_distribution<double> azSampler{0.0, 2 * M_PI};
    std::uniform_real_distribution<double> elSampler{0.0, M_PI};
    std::uniform_real_distribution<double> lengthSampler{0.0, 1.0};
    using PositionList = std::vector<std::vector<double>>;
    using AngleList = std::vector<std::vector<double>>;
    PositionList tipPositions;
    AngleList angles;
public:
    static bool
    checkForBackwardGrowth(double previousAz, double previousEl, double newAz, double newEl, double threshold);

    PositionList getTipPositions() { return tipPositions; }

    std::shared_ptr<OccupiedSpace> occupiedSpaceCenters;

    Axon();

    ~Axon() {};

    void growthStep(double i);

    void run();

    static double angleDifferenceCalculator(double a1, double a2);
};


#endif //TUMORSIMULATION_AXON_H
