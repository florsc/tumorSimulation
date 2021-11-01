#include <gtest/gtest.h>
#include "../util/HelperFunctions.h"
#include <cmath>
#include <fstream>


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


void compareEuclideanVector(EuclideanVector e1, EuclideanVector e2, double dist){
    EXPECT_NEAR(e1[0], e2[0], dist);
    EXPECT_NEAR(e1[1], e2[1], dist);
    EXPECT_NEAR(e1[2], e2[2], dist);
}

TEST(Test, sphericalCoordinateTestValues) {
    compareEuclideanVector(HelperFunctions::sph2cart(0.9272, 0.7853, 7.0710),
                           EuclideanVector(3, 4, 5),0.01);
    compareEuclideanVector(HelperFunctions::sph2cart(1.2, 0.5*M_PI-0.6, 10.6),
                           EuclideanVector(2.17, 5.58, 8.75),0.01);
    auto vector = HelperFunctions::sph2cart(1.5616, 1.17, 12.2);
    EXPECT_NEAR(vector.GetEuclideanNorm(), 12.2,0.01);
}

TEST(Test, euclideanCoordinateTest) {
    std::vector<double> azVec({0.0, 0.2,0.9,1.2,1.9, 2.7, 3.05, 0.5*M_PI,M_PI,1.5*M_PI,2*M_PI});
    std::vector<double> elVec({- 0.5*M_PI, -1.5, -1.2, -0.811, 0.3, 0.0, 0.2,0.5,0.9,1.2,1.45, 0.5*M_PI});
    std::vector<double> lengthVec({0.1, 1.1, 10.0});
    for(const auto& el:elVec){
        for(const auto& az:azVec){
            for(const auto& length:lengthVec){
                auto sphericalAngles = HelperFunctions::getSphericalAngles(HelperFunctions::sph2cart(az, el, length));
                EXPECT_NEAR(sphericalAngles.first, az,0.01);
                EXPECT_NEAR(sphericalAngles.second, el,0.01);

            }
        }
    }

}

TEST(Test, euclideanCoordinateRandomTestValues) {
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    GeneratorHandle generator;
    std::ofstream testSeedFile;
    testSeedFile.open("testSeeds.txt", std::ios_base::app);
    testSeedFile << seed << "\n";
    testSeedFile.close();
    auto azDist = std::uniform_real_distribution(0.0,2*M_PI);
    auto elDist = std::uniform_real_distribution(-0.5 *M_PI,0.5*M_PI);
    auto lengthDist = std::uniform_real_distribution(0.01,100.0);
    auto angle1 = azDist(*generator);
    auto angle2 = elDist(*generator);
    auto length = lengthDist(*generator);
    auto sphericalAngles = HelperFunctions::getSphericalAngles(HelperFunctions::sph2cart(angle1, angle2, length));
    EXPECT_NEAR(sphericalAngles.first, angle1,0.01);
    EXPECT_NEAR(sphericalAngles.second, angle2,0.01);
}

TEST(Test, sphericalEuclideanTest) {
    compareEuclideanVector(HelperFunctions::sph2cart(0.9272, 0.7853, 7.0710),
                           EuclideanVector(3, 4, 5),0.01);
    compareEuclideanVector(HelperFunctions::sph2cart(1.2, 0.5*M_PI-0.6, 10.6),
                           EuclideanVector(2.17, 5.58, 8.75),0.01);
    auto vector = HelperFunctions::sph2cart(1.5616, 1.17, 12.2);
    EXPECT_NEAR(vector.GetEuclideanNorm(), 12.2,0.01);
}


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
