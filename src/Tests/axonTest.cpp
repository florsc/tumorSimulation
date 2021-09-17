//
// Created by florian on 9/14/21.
//

#include <gtest/gtest.h>
#include "../Axon.h"

TEST(Test, AngleDifferenceCalculator) {
    EXPECT_NEAR(Axon::angleDifferenceCalculator(1, 2), 1, 0.01);
    EXPECT_NEAR(Axon::angleDifferenceCalculator(0.1, 2 * M_PI - 0.1), 0.2, 0.01);
    EXPECT_NEAR(Axon::angleDifferenceCalculator(1, 1 + M_PI), M_PI, 0.01);
    EXPECT_NEAR(Axon::angleDifferenceCalculator(3, 2), 1, 0.01);
    EXPECT_NEAR(Axon::angleDifferenceCalculator(2 * M_PI - 0.5, 0.3), 0.8, 0.01);
}

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
