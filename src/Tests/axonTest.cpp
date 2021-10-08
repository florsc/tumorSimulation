//
// Created by florian on 9/14/21.
//

#include <gtest/gtest.h>
#include "../Axon.h"

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
void checkCenterEquality(std::initializer_list<double> start, std::initializer_list<double> end,
                         std::initializer_list<std::initializer_list<double>> expectedResults) {
    auto calculatedCenters = Axon::createCenters(EuclideanVector(start), EuclideanVector(end));
    EXPECT_EQ(calculatedCenters.size(), expectedResults.size());
    if (calculatedCenters.size() == expectedResults.size()) {
        auto expectedResultVector = std::vector<std::vector<double>>();
        for (const auto &expectedResult: expectedResults) {
            expectedResultVector.emplace_back(expectedResult);
        }
        for (int i = 0; i < calculatedCenters.size(); i++) {
            for (int j = 0; j < 3; j++) {
                EXPECT_NEAR(calculatedCenters.at(i).at(j), expectedResultVector.at(i).at(j), 0.001);
            }
        }
    }
}

TEST(Test, CenterCreation) {
    checkCenterEquality({1, 1, 1}, {0.2, 0, 0}, {{1.1, 1, 1},
                                                 {1.2, 1, 1}});
    checkCenterEquality({1, 1, 1}, {0.24, 0, 0}, {{1.12, 1, 1},
                                                  {1.24, 1, 1}});
    checkCenterEquality({1, 1, 1}, {0.33, 0.44, 0}, {{1.066, 1.088, 1},
                                                     {1.132, 1.176, 1},
                                                     {1.198, 1.264, 1},
                                                     {1.264, 1.352, 1},
                                                     {1.33,  1.44,  1}});
    checkCenterEquality({1, 1, 1}, {0.001, 0.001, 0.001}, {});
}
