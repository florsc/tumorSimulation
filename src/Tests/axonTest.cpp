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
#include "../SimulationSetUp/TargetSetUp/SphericalTargetSetUpParameters.h"
#include "../Axons/Factories/RazettiFactory.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::internal::GetWithoutMatchers;

class AxonTest : public ::testing::Test {
public:
    AxonFactoryHandle
    getAxonFactory(std::shared_ptr<SimulationManager> simulationManager) { return simulationManager->m_axonFactory; }

    BaseAxonParameters &
    getFactoryParameters(AxonFactoryHandle axonFactory) { return axonFactory->m_baseAxonParameters; }

    RazettiAxonParameters &
    getFactoryParameters(std::shared_ptr<RazettiFactory> axonFactory) { return axonFactory->m_razettiAxonParameters; }

    BaseAxonParameters &getAxonParameters(AxonHandle axon) { return axon->m_baseAxonParameters; }

    RazettiAxonParameters &
    getAxonParameters(std::shared_ptr<RazettiAxon> axon) { return axon->m_razettiAxonParameters; }
};

class FakeConstraintManager : public ConstraintManager {
public:
    FakeConstraintManager(ParameterStruct &parameters) : ConstraintManager(parameters) {}

    virtual bool checkForConstraint(const PositionVector &positions) const override { return false; }
};

class MockConstraintManager : public FakeConstraintManager {
public:
    MockConstraintManager(ParameterStruct &parameters) : FakeConstraintManager(parameters) {}

    MOCK_METHOD(bool, checkForConstraint, (const PositionVector& positions), (const, override));
    MOCK_METHOD(void, addConstraintCenters, (const PositionVector& positions, int axonIdentifier,
            int growthStep), (override));
};

TEST_F(AxonTest, CheckConstraintManagerCalls) {
    testing::InSequence s;
    ParameterStruct parameters;
    auto razettiSetUpParameters = std::make_shared<RazettiSetUpParameters>();
    razettiSetUpParameters->branchingProbability = 0;
    parameters.axonSetUpParameters = razettiSetUpParameters;
    ConstraintManagerHandle constraintManager = std::make_shared<MockConstraintManager>(parameters);
    auto simulationManager = std::make_shared<SimulationManager>(parameters);
    simulationManager->setUp(parameters, simulationManager);
    auto axonFactory = getAxonFactory(simulationManager);
    getFactoryParameters(axonFactory).constraintManager = constraintManager;
    auto axon = axonFactory->makeAxon(EuclideanVector(0, 0, 0));
    auto mockConstraintManager = dynamic_cast<MockConstraintManager *>(constraintManager.get());

    EXPECT_CALL(*mockConstraintManager, checkForConstraint).Times(
            testing::Exactly(razettiSetUpParameters->numberOfGrowthStepsEachStep));
    EXPECT_CALL(*mockConstraintManager, addConstraintCenters).Times(testing::Exactly(1));
    axon->grow();
}

class MockTargetManager : public TargetManager {
public:
    explicit MockTargetManager(TargetSetUpVector targets) : TargetManager(targets) {};
    MOCK_METHOD(bool, checkTargetReached, (const EuclideanVector& position), (const));
    MOCK_METHOD(EuclideanVector, calculateForce, (const EuclideanVector& position), (const));
};

TEST_F(AxonTest, CheckTargetManagerCalls) {
    ParameterStruct parameters;
    auto sphericalTargetSetUp1 = std::make_shared<SphericalTargetSetUpParameters>();
    auto sphericalTargetSetUp2 = std::make_shared<SphericalTargetSetUpParameters>();
    sphericalTargetSetUp1->centerPoint = EuclideanVector({12, 70, 20});
    sphericalTargetSetUp2->centerPoint = EuclideanVector({-120, 5, -20});
    sphericalTargetSetUp1->radius = 1;
    sphericalTargetSetUp2->radius = 1;
    parameters.targets = TargetSetUpVector({sphericalTargetSetUp1,
                                            sphericalTargetSetUp2});
    TargetManagerHandle targetManager = std::make_shared<MockTargetManager>(parameters.targets);
    auto simulationManager = std::make_shared<SimulationManager>(parameters);
    simulationManager->setUp(parameters, simulationManager);
    auto axonFactory = getAxonFactory(simulationManager);
    getFactoryParameters(axonFactory).targetManager = targetManager;
    auto axon = axonFactory->makeAxon(EuclideanVector(0, 0, 0));
    auto mockTargetManager = dynamic_cast<MockTargetManager *>(targetManager.get());

    //EXPECT_CALL(*mockTargetManager, calculateForce).Times(testing::AtLeast(2));
    EXPECT_CALL(*mockTargetManager, checkTargetReached).Times(testing::AtLeast(2));
    axon->grow();
}


TEST_F(AxonTest, CheckCorrectParameterTransfer) {
    ParameterStruct parameters;
    auto razettiSetUpParameters = std::make_shared<RazettiSetUpParameters>();
    parameters.axonSetUpParameters = razettiSetUpParameters;
    auto simulationManager = std::make_shared<SimulationManager>(parameters);
    simulationManager->setUp(parameters, simulationManager);
    auto axonFactory = getAxonFactory(simulationManager);
    auto baseParameters = getFactoryParameters(axonFactory);

    EXPECT_EQ(baseParameters.maxNumberOfConstraintEncounters, razettiSetUpParameters->maxNumberOfConstraintEncounters);
    EXPECT_EQ(baseParameters.branchingProbability, razettiSetUpParameters->branchingProbability);
    EXPECT_EQ(*baseParameters.constraintManager, ConstraintManager(parameters));
    auto razettiFactory = std::dynamic_pointer_cast<RazettiFactory>(axonFactory);
    auto razettiParameters = getFactoryParameters(razettiFactory);
    EXPECT_EQ(razettiParameters.numberOfRetractions, razettiSetUpParameters->numberOfRetractions);
    EXPECT_EQ(razettiParameters.maxNumberOfConstraintEncountersEachSubstep,
              razettiSetUpParameters->maxNumberOfConstraintEncountersEachSubstep);
    EXPECT_EQ(razettiParameters.numberOfSubstepsEachStep, razettiSetUpParameters->numberOfGrowthStepsEachStep);
    EXPECT_EQ(razettiParameters.beta, razettiSetUpParameters->beta);
    EXPECT_EQ(razettiParameters.lengthSampler, razettiSetUpParameters->lengthSampler);

    auto axon = axonFactory->makeAxon(EuclideanVector(0, 0, 0));
    auto baseAxonParameters = getAxonParameters(axon);
    EXPECT_EQ(baseAxonParameters.maxNumberOfConstraintEncounters,
              razettiSetUpParameters->maxNumberOfConstraintEncounters);
    EXPECT_EQ(baseAxonParameters.branchingProbability, razettiSetUpParameters->branchingProbability);
    EXPECT_EQ(*baseAxonParameters.constraintManager, ConstraintManager(parameters));

    auto razettiAxon = std::dynamic_pointer_cast<RazettiAxon>(axon);
    auto razettiAxonParameters = getAxonParameters(razettiAxon);

    EXPECT_EQ(razettiAxonParameters.numberOfRetractions, razettiSetUpParameters->numberOfRetractions);
    EXPECT_EQ(razettiAxonParameters.maxNumberOfConstraintEncountersEachSubstep,
              razettiSetUpParameters->maxNumberOfConstraintEncountersEachSubstep);
    EXPECT_EQ(razettiAxonParameters.numberOfSubstepsEachStep, razettiSetUpParameters->numberOfGrowthStepsEachStep);
    EXPECT_EQ(razettiAxonParameters.beta, razettiSetUpParameters->beta);
    EXPECT_EQ(razettiAxonParameters.lengthSampler, razettiSetUpParameters->lengthSampler);


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