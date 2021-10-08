#include <gtest/gtest.h>
#include "../HelperFunctions.h"
#include <cmath>

// Demonstrate some basic assertions.
using SpatialVector = std::vector<double>;

void checkDoubleVectorEquality(SpatialVector v1, SpatialVector v2) {
    EXPECT_NEAR(v1[0], v2[0], 0.001);
    EXPECT_NEAR(v1[1], v2[1], 0.001);
    EXPECT_NEAR(v1[2], v2[2], 0.001);

}

TEST(Test, sphericalCoordinateFunctionBasic) {
    EXPECT_EQ(HelperFunctions::sph2cart(0, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, M_PI, 1), SpatialVector({0, 0, -1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 2 * M_PI, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(2 * M_PI, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, M_PI / 2, 1), SpatialVector({1, 0, 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 2, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -M_PI, 1), SpatialVector({0, 0, -1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -2 * M_PI, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-2 * M_PI, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -M_PI / 2, 1), SpatialVector({-1, 0, 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 2, 0, 1), SpatialVector({0, 0, 1}));
}

TEST(Test, sphericalCoordinateFunctionComplex) {
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI, M_PI, 1), SpatialVector({0, 0, -1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 4, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, M_PI / 4, 1), SpatialVector({sqrt(0.5), 0, sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 4, M_PI / 4, 1),
                              SpatialVector({sqrt(0.25), sqrt(0.25), sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 4, 0, 1), SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, -M_PI / 4, 1), SpatialVector({-sqrt(0.5), 0, sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 4, -M_PI / 4, 1),
                              SpatialVector({-sqrt(0.25), sqrt(0.25), sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(M_PI / 4, -M_PI / 4, 1),
                              SpatialVector({-sqrt(0.25), -sqrt(0.25), sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(-M_PI / 4, M_PI / 4, 1),
                              SpatialVector({sqrt(0.25), -sqrt(0.25), sqrt(0.5)}));

    checkDoubleVectorEquality(HelperFunctions::sph2cart(3 * M_PI / 4, 0, 1),
                              SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(5 * M_PI / 4, 0, 1),
                              SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(7 * M_PI / 4, 0, 1),
                              SpatialVector({0, 0, 1}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(3 * M_PI / 4, M_PI / 2, 1),
                              SpatialVector({-sqrt(0.5), sqrt(0.5), 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(5 * M_PI / 4, M_PI / 2, 1),
                              SpatialVector({-sqrt(0.5), -sqrt(0.5), 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(7 * M_PI / 4, M_PI / 2, 1),
                              SpatialVector({sqrt(0.5), -sqrt(0.5), 0}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 3 * M_PI / 4, 1),
                              SpatialVector({sqrt(0.5), 0, -sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 5 * M_PI / 4, 1),
                              SpatialVector({-sqrt(0.5), 0, -sqrt(0.5)}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0, 7 * M_PI / 4, 1),
                              SpatialVector({-sqrt(0.5), 0, sqrt(0.5)}));
}

TEST(Test, sphericalCoordinateTestValues) {
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0.9272, 0.7853, 7.0710),
                              SpatialVector({3, 4, 5}));
    checkDoubleVectorEquality(HelperFunctions::sph2cart(0.1616, 1.1837, 10.066),
                              SpatialVector({9.2, 1.5, 3.8}));
}
