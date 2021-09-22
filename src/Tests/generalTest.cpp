//
// Created by florian on 9/14/21.
//

//
// Created by florian on 9/14/21.
//

#include <gtest/gtest.h>
#include "../SimulationLibrary.h"


TEST(Test, BasicAssertions) {
    try {
        run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
