//
// Created by florian on 9/22/21.
//

#include "../Managers/ConstraintManager.h"
#include "../SimulationSetUp/ConstraintSetUp/SphericalLimitSetUpParameters.h"
#include "../ExteriorLimits/ExteriorLimit.h"
#include <gtest/gtest.h>

class ConstraintHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        ParameterStruct parameters;
        auto sphericalLimitSetUp = std::make_shared<SphericalLimitSetUpParameters>();
        sphericalLimitSetUp->radius=100;
        parameters.exteriorLimitSetUpParameters=sphericalLimitSetUp;
        m_constraintHandler = std::make_shared<ConstraintManager>(parameters);
        m_constraintHandler->addConstraintCenters(
                std::vector<EuclideanVector>({EuclideanVector({1, 1, 1}), EuclideanVector({1, 2, 2})}));
    }
    ConstraintManagerHandle m_constraintHandler;
public:
    ConstraintHandlerTest(){}
    // void TearDown() override {}

};

TEST_F(ConstraintHandlerTest, checkOccupiedSpace) {
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1.009, 1, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1.009, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1, 1.009})})));
    EXPECT_TRUE(
            m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1.005, 1.005, 1})})));
    EXPECT_TRUE(
            m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1.005, 1, 1.005})})));
    EXPECT_TRUE(
            m_constraintHandler->checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1.005, 1.005})})));

    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.009, 1, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1.009, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1, 1.009})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.005, 1.005, 1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.005, 1, 1.005})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1.005, 1.005})})));

    EXPECT_FALSE(m_constraintHandler->checkForConstraintAndAdd(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.1, 1.1, 1.1})}), 1, 1));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.1, 1.1, 1.1})})));
    EXPECT_TRUE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.1, 1.1, 1.1})})));
    m_constraintHandler->freeSpace(1, {1});
    EXPECT_FALSE(m_constraintHandler->checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.1, 1.1, 1.1})})));
}
