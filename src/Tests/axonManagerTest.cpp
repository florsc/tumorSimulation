//
// Created by florian on 10/27/21.
//


#include <gtest/gtest.h>
#include "../Managers/AxonManagers/AxonManager.h"
#include "../Managers/SimulationManager.h"
#include "../Managers/AxonManagers/AxonManagerLinear.h"
#include "../Managers/AxonManagers/AxonManagerWaitingTime.h"
#include "../Axons/Factories/RazettiFactory.h"
#include "../util/EuclideanVector.h"
#include "../Axons/AxonTypes/RazettiAxon/RazettiAxon.h"

TEST(Test, checkLinearOrder) {
    AxonManagerLinear axonManager = AxonManagerLinear(std::make_shared<AxonOrderLinearData>());
    auto factory = RazettiFactory(std::make_shared<RazettiSetUpParameters>());
    ParameterStruct parameters;
    auto simulationManager = std::make_shared<SimulationManager>(parameters);
    factory.setUpFactory(simulationManager);
    axonManager.addAxon(factory.makeAxon(EuclideanVector(0,0,0)));
    axonManager.addAxon(factory.makeAxon(EuclideanVector(1,0,0)));
    axonManager.addAxon(factory.makeAxon(EuclideanVector(2,0,0)));
    for(int i = 0;i<10;i++){
        auto currentAxon = axonManager.getNextAxon();
        auto axonPosition = currentAxon->getTipPositions().back();
        EXPECT_NEAR(axonPosition[0],double(i%3),0.01);
    }
}

TEST(Test, checkWaitingTimeOrder) {
    SamplerHandle testSampler(new FixedValuesSampler({1, 3, 4, 1, 4, 5, 1, 8, 3, 4, 7, 9, 2, 4}));
    auto axonOrderSampledWaitingTimeData = std::make_shared<AxonOrderSampledWaitingTimeData>();
    axonOrderSampledWaitingTimeData->waitingTimeSampler = testSampler;
    axonOrderSampledWaitingTimeData->maximumTime=10.0;
    AxonManagerWaitingTime axonManager = AxonManagerWaitingTime(axonOrderSampledWaitingTimeData);
    auto factory = RazettiFactory(std::make_shared<RazettiSetUpParameters>());
    axonManager.addAxon(factory.makeAxon(EuclideanVector(0,0,0)));
    axonManager.addAxon(factory.makeAxon(EuclideanVector(1,0,0)));
    axonManager.addAxon(factory.makeAxon(EuclideanVector(2,0,0)));
    //sampled waiting times: 1,3,4,1,4,5,1,8,3,4,7,9,2,4
    //axon grow times (max 10):
    //0: 1     2 6           9       13>10
    //1:   3       8           12>10
    //2:     4       5 13>10
    //order: 0, 0, 1, 2, 2, 0, 1, 0
    auto order = std::vector<double>({0,0,1,2,2,0,1,0});
    for(auto it = order.begin();it != order.end();it++){
        auto currentAxon = axonManager.getNextAxon();
        auto axonPosition = currentAxon->getTipPositions().back();
        EXPECT_NEAR(axonPosition[0],double(*it),0.01);
    }
    EXPECT_EQ(nullptr ,axonManager.getNextAxon());
}