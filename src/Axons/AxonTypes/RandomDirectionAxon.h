//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONAXON_H
#define TUMORSIMULATION_RANDOMDIRECTIONAXON_H


#include <random>
#include "../../util/EuclideanVector.h"
#include "../../util/TypeDefs.h"
#include "BaseAxon.h"

class SimulationManager;

class RandomDirectionAxon : public BaseAxon{

    SamplerHandle m_lengthSampler;
    int m_maxConstraintEncounters;
    int m_numberOfGrowthTimes{0};
    int m_constraintCounter{0};
    std::normal_distribution<double> m_normalDistribution{0, 1};

public:
    RandomDirectionAxon(int maxConstraintEncounters, SamplerHandle lengthSampler, EuclideanVector startPosition,
                ConstraintManagerHandle constraintManager, SimulationManagerHandle simulationManager);

    void grow() override;

    bool addPosition(EuclideanVector position);

private:
    EuclideanVector sampleVector();

    void checkStopCondition();

    void checkTargetReached() {};

    bool checkBranching();

    void createNewBranch();

};


#endif //TUMORSIMULATION_RANDOMDIRECTIONAXON_H
