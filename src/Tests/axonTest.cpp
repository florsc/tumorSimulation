//
// Created by florian on 9/14/21.
//

#include <gtest/gtest.h>
#include "../util/HelperFunctions.h"
#include "../Managers/ConstraintManager.h"
#include "../Managers/TargetManager.h"
#include "../Managers/SimulationManager.h"
#include "gmock/gmock.h"
#include "../Axons/AxonTypes/BaseAxon/BaseAxon.h"
#include "../Axons/AxonTypes/RazettiAxon/RazettiAxon.h"
#include "../Targets/SphericalTarget.h"
#include "../SimulationSetUp/GrowthModels/RazettiSetUpParameters.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::internal::GetWithoutMatchers;

class AxonTest :public ::testing::Test{
public:
    AxonFactoryHandle getAxonFactory(std::shared_ptr<SimulationManager> simulationManager){return simulationManager->m_axonFactory; }
    BaseAxonParameters& getFactoryParameters(AxonFactoryHandle axonFactory){return axonFactory->m_baseAxonParameters;}
    RazettiAxonParameters& getFactoryParameters(std::shared_ptr<RazettiFactory> axonFactory){return axonFactory->m_razettiAxonParameters;}
    BaseAxonParameters& getAxonParameters(AxonHandle axon){return axon->m_baseAxonParameters;}
    RazettiAxonParameters& getAxonParameters(std::shared_ptr<RazettiAxon> axon){return axon->m_razettiAxonParameters;}
};

class FakeConstraintManager : public ConstraintManager {
public:
    virtual bool checkForConstraint(const PositionVector& positions) const override {return false;}
};
class MockConstraintManager : public FakeConstraintManager {
public:
    MOCK_METHOD(bool, checkForConstraint, (const PositionVector& positions), (const, override));
    MOCK_METHOD(void, addConstraintCenters, (const PositionVector& positions,  int axonIdentifier,
            int growthStep), ( override));
};
TEST_F(AxonTest, CheckConstraintManagerCalls) {
    testing::InSequence s;
    parameters.init();
    ConstraintManagerHandle constraintManager = std::make_shared<MockConstraintManager>();
    auto simulationManager = std::make_shared<SimulationManager>();
    simulationManager->setUp(simulationManager, 0.0);
    auto axonFactory = getAxonFactory(simulationManager);
    getFactoryParameters(axonFactory).constraintManager=constraintManager;
    auto axon = axonFactory->makeAxon(EuclideanVector(0,0,0));
    auto mockConstraintManager = dynamic_cast<MockConstraintManager*>(constraintManager.get());

    EXPECT_CALL(*mockConstraintManager, checkForConstraint).Times(testing::Exactly(RazettiSetUpParameters::numberOfGrowthStepsEachStep));
    EXPECT_CALL(*mockConstraintManager, addConstraintCenters).Times(testing::Exactly(1));
    axon->grow();
}

class MockTargetManager : public TargetManager {
public:
    explicit MockTargetManager(TargetVector targets):TargetManager(targets){};
    MOCK_METHOD(bool, checkTargetReached, (const EuclideanVector& position), (const));
    MOCK_METHOD(EuclideanVector, calculateForce, (const EuclideanVector& position), (const));
};
TEST_F(AxonTest, CheckTargetManagerCalls) {
    parameters.init();
    TargetManagerHandle targetManager = std::make_shared<MockTargetManager>(TargetVector({TargetHandle(new SphericalTarget({12, 70, 20}, 1,1)),
                                                                             TargetHandle(new SphericalTarget({-120, 5, -20}, 1,1))}));
    auto simulationManager = std::make_shared<SimulationManager>();
    simulationManager->setUp(simulationManager,0);
    auto axonFactory = getAxonFactory(simulationManager);
    getFactoryParameters(axonFactory).targetManager=targetManager;
    auto axon = axonFactory->makeAxon(EuclideanVector(0,0,0));
    auto mockTargetManager = dynamic_cast<MockTargetManager*>(targetManager.get());

    EXPECT_CALL(*mockTargetManager, calculateForce).Times(testing::AtLeast(2));
    EXPECT_CALL(*mockTargetManager, checkTargetReached).Times(testing::AtLeast(2));
    axon->grow();
}


TEST_F(AxonTest, CheckCorrectParameterTransfer) {
    parameters.init();
    auto simulationManager = std::make_shared<SimulationManager>();
    simulationManager->setUp(simulationManager);
    auto axonFactory = getAxonFactory(simulationManager);
    auto baseParameters = getFactoryParameters(axonFactory);
    EXPECT_EQ(baseParameters.maxNumberOfConstraintEncounters, AxonSetUpParameters::maxNumberOfConstraintEncounters);
    EXPECT_EQ(baseParameters.branchingProbability, AxonSetUpParameters::branchingProbability);
    EXPECT_EQ(*baseParameters.constraintManager, ConstraintManager(parameters.exteriorLimit,ParameterStruct::minDistance));
    auto razettiFactory = std::dynamic_pointer_cast<RazettiFactory>(axonFactory);
    auto razettiParameters = getFactoryParameters(razettiFactory);
    EXPECT_EQ(razettiParameters.numberOfRetractions, RazettiSetUpParameters::numberOfRetractions);
    EXPECT_EQ(razettiParameters.maxNumberOfConstraintEncountersEachSubstep, RazettiSetUpParameters::maxNumberOfConstraintEncountersEachSubstep);
    EXPECT_EQ(razettiParameters.numberOfSubstepsEachStep, RazettiSetUpParameters::numberOfGrowthStepsEachStep);
    EXPECT_EQ(razettiParameters.beta, RazettiSetUpParameters::beta);
    EXPECT_EQ(razettiParameters.alpha, RazettiSetUpParameters::alpha);
    //EXPECT_EQ(razettiParameters.lengthSampler, razettiSetUpParameters.lengthSampler);

    auto axon = axonFactory->makeAxon(EuclideanVector(0,0,0));
    auto baseAxonParameters = getAxonParameters(axon);
    EXPECT_EQ(baseAxonParameters.maxNumberOfConstraintEncounters, AxonSetUpParameters::maxNumberOfConstraintEncounters);
    EXPECT_EQ(baseAxonParameters.branchingProbability, AxonSetUpParameters::branchingProbability);
    EXPECT_EQ(*baseAxonParameters.constraintManager, ConstraintManager(parameters.exteriorLimit,ParameterStruct::minDistance));

    auto razettiAxon = std::dynamic_pointer_cast<RazettiAxon>(axon);
    auto razettiAxonParameters = getAxonParameters(razettiAxon);

    EXPECT_EQ(razettiAxonParameters.numberOfRetractions, RazettiSetUpParameters::numberOfRetractions);
    EXPECT_EQ(razettiAxonParameters.maxNumberOfConstraintEncountersEachSubstep, RazettiSetUpParameters::maxNumberOfConstraintEncountersEachSubstep);
    EXPECT_EQ(razettiAxonParameters.numberOfSubstepsEachStep, RazettiSetUpParameters::numberOfGrowthStepsEachStep);
    EXPECT_EQ(razettiAxonParameters.beta, RazettiSetUpParameters::beta);
    EXPECT_EQ(razettiAxonParameters.alpha, RazettiSetUpParameters::alpha);
    //EXPECT_EQ(razettiAxonParameters.lengthSampler, razettiSetUpParameters.lengthSampler);


}

/*
TEST(Test, CheckForBackwardGrowth) {
    EXPECT_FALSE(Axon::checkForBackwardGrowth(1, 2, 1, 2, 0.01));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(0, 0.01, 0, M_PI, 0.1));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(1, 0.01, 2, M_PI, 0.1));
    EXPECT_FALSE(Axon::checkForBackwardGrowth(1, 1, 0, 0.1, 0.4 * M_PI));
    EXPECT_FALSE(Axon::checkForBackwardGrowth(1, 1, 1, 1, 0.4 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(M_PI, 0.5 * M_PI, 0, 0.5 * M_PI, 0.01));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(M_PI, 0.4 * M_PI, 0, 0.5 * M_PI, 0.4));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(M_PI, 0.6 * M_PI, 0, 0.4 * M_PI, 0.1));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(1.25 * M_PI, 0.4 * M_PI, 0.25 * M_PI, 0.6 * M_PI, 0.1));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(1.05 * M_PI, 0.65 * M_PI, 0, 0.4 * M_PI, 0.3 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(1.3 * M_PI, 0.45 * M_PI, 0.25 * M_PI, 0.6 * M_PI, 0.3 * M_PI));
    EXPECT_FALSE(Axon::checkForBackwardGrowth(0.01 * M_PI, 0.01 * M_PI, 0.99 * M_PI, 0, 0.1));

    EXPECT_TRUE(Axon::checkForBackwardGrowth(0, 0.25 * M_PI, 1.05 * M_PI, 0.75 * M_PI, 0.1 * M_PI));
    EXPECT_FALSE(Axon::checkForBackwardGrowth(1.5 * M_PI, 1, 1.55 * M_PI, 1, 0.1 * M_PI));
    EXPECT_FALSE(Axon::checkForBackwardGrowth(0.75 * M_PI, 1.5, 0.25 * M_PI, 1.5, 0.1 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(0.2 * M_PI, 2, 0.8 * M_PI, 2, 0.5 * M_PI));

    EXPECT_TRUE(Axon::checkForBackwardGrowth(1, M_PI, 1, 0.05 * M_PI, 0.1 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(1, 0.25 * M_PI, 1, 1.3 * M_PI, 0.1 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(0.5, 0.02 * M_PI, 0.5, 1.04 * M_PI, 0.1 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(2, 0.5 * M_PI, 2, 1.1 * M_PI, 0.5 * M_PI));
    EXPECT_TRUE(Axon::checkForBackwardGrowth(1, 0.3 * M_PI, 1, 1.5 * M_PI, 0.9 * M_PI));

    EXPECT_TRUE(Axon::checkForBackwardGrowth(1.75 * M_PI, 0.25 * M_PI, 0.75 * M_PI, 0.75 * M_PI, 0.3 * M_PI));
}
*/