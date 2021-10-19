//
// Created by florian on 10/18/21.
//

#ifndef TUMORSIMULATION_RANDOMDIRECTION_H
#define TUMORSIMULATION_RANDOMDIRECTION_H


#include "GrowthModel.h"
#include "../../util/Samplers.h"

class RandomDirection : public GrowthModel {

    const int maxNumberOfConstraintEncounters = 1000;
    static constexpr double angleBackwardThreshold = 0.7 * M_PI;
    SamplerHandle lengthSampler = std::make_shared<ConstantValueSampler>(1);

public:
    RandomDirection() : GrowthModel() {}

    AxonFactoryHandle makeAxonFactory(SimulationManagerHandle simulationManager) override;
};


#endif //TUMORSIMULATION_RANDOMDIRECTION_H
