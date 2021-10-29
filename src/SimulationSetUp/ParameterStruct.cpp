//
// Created by florian on 9/29/21.
//

#include <fstream>
#include "ParameterStruct.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include "GrowthModels/RazettiSetUpParameters.h"
#include "GrowthModels/RandomDirectionSetUpParameters.h"
#include "AxonOrder/AxonOrderSampledWaitingTime.h"
#include "../Targets/SphericalTarget.h"
#include "../Axons/Factories/RandomDirectionFactory.h"
#include "AxonOrder/AxonOrderLinear.h"

ParameterStruct::ParameterStruct() : m_generator(new std::mt19937(
        seed)) {
    std::ofstream seedFile;
    seedFile.open("seeds.txt", std::ios_base::app);
    seedFile << seed << "\n";
    seedFile.close();
}

void ParameterStruct::init() {
    exteriorLimit = std::shared_ptr<ExteriorLimit>(new SphericalLimit(200));
    axonOrder = std::make_unique<AxonOrderLinear>();
    targets = TargetVector({TargetHandle(new SphericalTarget({12, 70, 20}, 20,10)),
                            TargetHandle(new SphericalTarget({-120, 5, -20}, 30,10))});
    axonFactory = std::make_shared<RazettiFactory>();
}

ParameterStruct parameters;