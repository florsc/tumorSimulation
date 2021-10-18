//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_RAZETTIAXON_H
#define TUMORSIMULATION_RAZETTIAXON_H


#include <vector>
#include "BaseAxon.h"

class RazettiAxon : public BaseAxon {
    std::vector<int> m_timeStepIndices;
    std::vector<std::pair<double, double>> m_growthAngles;
    int m_GrowthStepsEachTimeStep;
    int m_maxConstraintsEachTimeStep{2};
    int m_numberOfRetractions;
    double m_alpha;
    double m_beta;
    double m_stepLength;
    int m_maxConstraintEncounters;
    int m_numberOfGrowthTimes{0};
    int m_constraintCounter{0};

public:
    RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions,
                int maxConstraintEncounters, double alpha, double beta,
                double stepLength, EuclideanVector startPosition, EuclideanVector nextPosition,
                ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager);

    RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions,
                int maxConstraintEncounters, double alpha, double beta,
                double stepLength, EuclideanVector startPosition, ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager);

    RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions,
                int maxConstraintEncounters, double alpha, double beta,
                double stepLength, const EuclideanVector &startPosition,
                std::pair<double, double> startingAngles, ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager);

    void grow() override;

    void addPosition(EuclideanVector position);

    void addPosition(EuclideanVector position, std::pair<double, double>);

private:
    EuclideanVector sampleVector();

    void checkStopCondition();

    void checkTargetReached() {};

    bool checkBranching();

    void createNewBranch(const PositionVector& possibleStartingPoints);

};


#endif //TUMORSIMULATION_RAZETTIAXON_H
