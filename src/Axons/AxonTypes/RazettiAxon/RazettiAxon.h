//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_RAZETTIAXON_H
#define TUMORSIMULATION_RAZETTIAXON_H


#include <vector>
#include "../BaseAxon/BaseAxon.h"
#include "RazettiAxonParameters.h"

class RazettiAxon : public BaseAxon {
    std::vector<int> m_growthStepIndices;
    std::vector<std::pair<double, double>> m_growthAnglesParameters;
    int m_numberOfGrowthTimes{0};

    RazettiAxonParameters m_razettiAxonParameters;

public:
    RazettiAxon(const EuclideanVector &startPosition, RazettiAxonParameters razettiAxonParameters,
                BaseAxonParameters baseAxonParameters, int constraintsEncountered = 0);

    RazettiAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition,
                RazettiAxonParameters razettiAxonParameters, BaseAxonParameters baseAxonParameters,
                int constraintsEncountered = 0);


    void grow() override;

    bool addPosition(const EuclideanVector &position);

    bool addPosition(const EuclideanVector &position, std::pair<double, double>);

private:
    EuclideanVector sampleVector();

    void setUpNewBranch(const PositionVector &possibleStartingPoints);

    friend class AxonTest;
};


#endif //TUMORSIMULATION_RAZETTIAXON_H
