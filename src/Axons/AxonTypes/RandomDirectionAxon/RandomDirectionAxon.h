//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTIONAXON_H
#define TUMORSIMULATION_RANDOMDIRECTIONAXON_H


#include <random>
#include "../../../util/EuclideanVector.h"
#include "../../../util/TypeDefs.h"
#include "../BaseAxon/BaseAxon.h"
#include "RandomDirectionAxonParameters.h"

class SimulationManager;

class RandomDirectionAxon : public BaseAxon {

    RandomDirectionAxonParameters m_randomDirectionAxonParameters;

    int m_numberOfGrowthTimes{0};

    std::normal_distribution<double> m_normalDistribution{0, 1};

public:
    RandomDirectionAxon(const EuclideanVector &startPosition, RandomDirectionAxonParameters randomDirectionAxonParameters,
                        BaseAxonParameters baseAxonParameters, int constraintsEncountered = 0);

    void grow() override;

    bool addPosition(const EuclideanVector& position);


private:
    EuclideanVector sampleVector();

    void setUpNewBranch();

};


#endif //TUMORSIMULATION_RANDOMDIRECTIONAXON_H
