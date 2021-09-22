//
// Created by florian on 9/22/21.
//

#include "../ConstraintHandler.h"
#include <gtest/gtest.h>

class ConstraintHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        constraintHandler.addConstraintCenters(
                std::vector<EuclideanVector>({EuclideanVector({1, 1, 1}), EuclideanVector({1, 2, 2})}));
    }

    ConstraintHandler constraintHandler;
public:
    ConstraintHandlerTest() : constraintHandler(std::shared_ptr<SphericalLimit>(new SphericalLimit(100))) {};
    // void TearDown() override {}

};

TEST_F(ConstraintHandlerTest, checkOccupiedSpace) {
    EXPECT_TRUE(constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1.009, 1, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1.009, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1, 1.009})})));
    EXPECT_TRUE(
            constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1.005, 1.005, 1})})));
    EXPECT_TRUE(
            constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1.005, 1, 1.005})})));
    EXPECT_TRUE(
            constraintHandler.checkForConstraint(std::vector<EuclideanVector>({EuclideanVector({1, 1.005, 1.005})})));

    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.009, 1, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1.009, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1, 1.009})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.005, 1.005, 1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.005, 1, 1.005})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1, 1.005, 1.005})})));

    EXPECT_FALSE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.1, 1.1, 1.1})})));
    EXPECT_TRUE(constraintHandler.checkForConstraint(
            std::vector<EuclideanVector>({EuclideanVector({0.9, 0.9, 0.9}), EuclideanVector({1.1, 1.1, 1.1})})));
}
