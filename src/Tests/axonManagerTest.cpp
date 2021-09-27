//
// Created by florian on 9/23/21.
//


#include <initializer_list>
#include <gtest/gtest.h>
#include "../AxonManager.h"

void checkStartPositionEquality(std::initializer_list<double> c1, std::initializer_list<double> c2,
                                std::initializer_list<std::initializer_list<double>> expectedStartPositions) {
    auto calculatedStartPositions = AxonManager::sampleStartPositions(EuclideanVector(c1), EuclideanVector(c2));

    EXPECT_EQ(calculatedStartPositions.size(), expectedStartPositions.size());
    if (calculatedStartPositions.size() == expectedStartPositions.size()) {
        auto expectedStartPositionsVector = std::vector<std::vector<double>>();
        for (const auto &expectedStartPosition: expectedStartPositions) {
            expectedStartPositionsVector.emplace_back(expectedStartPosition);
        }
        auto calculatedStartPositionsIter = calculatedStartPositions.begin();
        for (int i = 0; i < calculatedStartPositions.size(); i++) {
            for (int j = 0; j < 3; j++) {
                EXPECT_NEAR(calculatedStartPositionsIter->at(j), expectedStartPositionsVector.at(i).at(j), 0.001);
            }
            calculatedStartPositionsIter++;
        }
    }
}

TEST(Test, samplingStartValues) {
    checkStartPositionEquality({0, -0.1, -0.1}, {0, 0.1, 0.1}, {{0, -0.1, -0.1},
                                                                {0, -0.1, 0.1},
                                                                {0, 0.1,  -0.1},
                                                                {0, 0.1,  0.1}});
}