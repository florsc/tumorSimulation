//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_RAZETTIAXON_H
#define TUMORSIMULATION_RAZETTIAXON_H


#include <vector>
#include "BaseAxon.h"

class RazettiAxon : public BaseAxon {
    std::vector<int> m_growthStepIndices;
    std::vector<std::pair<double, double>> m_growthAngles;
    int m_substepsEachGrowthStep;
    int m_maxConstraintsEachGrowthStep;
    double m_alpha;
    double m_beta;
    SamplerHandle m_lengthSampler;
    int m_maxConstraintEncounters;
    int m_numberOfGrowthTimes{0};
    int m_constraintCounter{0};

public:
    RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions,
                int maxConstraintEncounters, double alpha, double beta,
                SamplerHandle lengthSampler, EuclideanVector startPosition, EuclideanVector nextPosition,
                ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager);

    RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions,
                int maxConstraintEncounters, double alpha, double beta,
                SamplerHandle lengthSampler, EuclideanVector startPosition, ConstraintManagerHandle constraintManager,
                SimulationManagerHandle simulationManager);

    RazettiAxon(int numberOfGrowthStepsEachTimeStep, int numberOfRetractions,
                int maxConstraintEncounters, double alpha, double beta,
                SamplerHandle lengthSampler, const EuclideanVector &startPosition,
                std::pair<double, double> startingAngles, ConstraintManagerHandle constraintManager,
                SimulationManagerHandle simulationManager);

    void grow() override;

    bool addPosition(EuclideanVector position);

    bool addPosition(EuclideanVector position, std::pair<double, double>);

private:
    EuclideanVector sampleVector();

    void checkStopCondition();

    bool checkBranching();

    void createNewBranch(const PositionVector &possibleStartingPoints);

};


#endif //TUMORSIMULATION_RAZETTIAXON_H
