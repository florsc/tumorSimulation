#include <gtest/gtest.h>
#include "../util/HelperFunctions.h"
#include <cmath>

// Demonstrate some basic assertions.
/*
void checkDoubleVectorEquality(EuclideanVector v1, EuclideanVector v2) {
    EXPECT_NEAR(v1[0], v2[0], 0.001);
    EXPECT_NEAR(v1[1], v2[1], 0.001);
    EXPECT_NEAR(v1[2], v2[2], 0.001);

}

TEST(Test, sphericalCoordinateFunctionBasic) {
    EXPECT_EQ(HelperFunctions::sph2cart(0, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, M_PI, 1), EuclideanVector({0, 0, -1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 2 * M_PI, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(2 * M_PI, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, M_PI / 2, 1), EuclideanVector({1, 0, 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 2, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -M_PI, 1), EuclideanVector({0, 0, -1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -2 * M_PI, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-2 * M_PI, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -M_PI / 2, 1), EuclideanVector({-1, 0, 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 2, 0, 1), EuclideanVector({0, 0, 1}));
}

TEST(Test, sphericalCoordinateFunctionComplex) {
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI, M_PI, 1), EuclideanVector({0, 0, -1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 4, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, M_PI / 4, 1), EuclideanVector({sqrt(0.5), 0, sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 4, M_PI / 4, 1),
                              EuclideanVector({sqrt(0.25), sqrt(0.25), sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 4, 0, 1), EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -M_PI / 4, 1), EuclideanVector({-sqrt(0.5), 0, sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 4, -M_PI / 4, 1),
                              EuclideanVector({-sqrt(0.25), sqrt(0.25), sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 4, -M_PI / 4, 1),
                              EuclideanVector({-sqrt(0.25), -sqrt(0.25), sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 4, M_PI / 4, 1),
                              EuclideanVector({sqrt(0.25), -sqrt(0.25), sqrt(0.5)}));

    checkDoubleVectorEquality(HelperFunctions::sph2cart(3 * M_PI / 4, 0, 1),
                              EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(5 * M_PI / 4, 0, 1),
                              EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(7 * M_PI / 4, 0, 1),
                              EuclideanVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(3 * M_PI / 4, M_PI / 2, 1),
                              EuclideanVector({-sqrt(0.5), sqrt(0.5), 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(5 * M_PI / 4, M_PI / 2, 1),
                              EuclideanVector({-sqrt(0.5), -sqrt(0.5), 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(7 * M_PI / 4, M_PI / 2, 1),
                              EuclideanVector({sqrt(0.5), -sqrt(0.5), 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 3 * M_PI / 4, 1),
                              EuclideanVector({sqrt(0.5), 0, -sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 5 * M_PI / 4, 1),
                              EuclideanVector({-sqrt(0.5), 0, -sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 7 * M_PI / 4, 1),
                              EuclideanVector({-sqrt(0.5), 0, sqrt(0.5)}));
}

TEST(Test, sphericalCoordinateTestValues) {
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0.9272, 0.7853, 7.0710),
                              EuclideanVector({3, 4, 5}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0.1616, 1.1837, 10.066),
                              EuclideanVector({9.2, 1.5, 3.8}));
}

*/

TEST(Test, removeElementsFromEndTest) {
    std::vector<int> vec({1, 2, 3, 4});
    HelperFunctions::removeElementsFromEnd(vec, 2);
    EXPECT_EQ(vec, std::vector<int>({1, 2}));
    std::list<int> list({1, 2, 3, 4});
    HelperFunctions::removeElementsFromEnd(list, 2);
    EXPECT_EQ(list, std::list<int>({1, 2}));
    HelperFunctions::removeElementsFromEnd(vec, 0);
    EXPECT_EQ(vec, std::vector<int>({1, 2}));
}


void checkCenterEquality(std::initializer_list<double> start, std::initializer_list<double> end,
                         std::initializer_list<std::initializer_list<double>> expectedResults) {
    auto calculatedCenters = HelperFunctions::createCoveringCenters(EuclideanVector(start), EuclideanVector(end), 0.1);
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
