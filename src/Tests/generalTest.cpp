//
// Created by florian on 9/14/21.
//

//
// Created by florian on 9/14/21.
//

#include <gtest/gtest.h>
#include <chrono>
#include "../SimulationLibrary.h"


TEST(Test, BasicAssertions) {
    try {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        run();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()
                  << "[µs]" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
