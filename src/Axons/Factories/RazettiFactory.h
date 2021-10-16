//
// Created by florian on 10/12/21.
//

#ifndef TUMORSIMULATION_RAZETTIFACTORY_H
#define TUMORSIMULATION_RAZETTIFACTORY_H

#include "AxonFactory.h"

class RazettiFactory : public AxonFactory {
    int m_numberOfGrowthStepsEachTimeStep;
    int m_numberOfRetractions;
    int m_maxNumberOfConstraintEncounters;
    double m_alpha;
    double m_beta;
    double m_stepLength;

public:
    RazettiFactory(int numberOfGrowthStepsEachTimeStep,
                   int numberOfRetractions, int maxNumberOfConstraintEncounters, double alpha, double beta,
                   double stepLength);

    AxonHandle makeAxon(const EuclideanVector &startPosition) override;

    AxonHandle makeStartedAxon(const EuclideanVector &startPosition, const EuclideanVector &nextPosition) override;

    AxonHandle makeDirectedAxon(const EuclideanVector &startPosition, const EuclideanVector &direction) override;
};

#endif //TUMORSIMULATION_RAZETTIFACTORY_H
