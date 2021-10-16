//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONORDERLINEAR_H
#define TUMORSIMULATION_AXONORDERLINEAR_H
#include "AxonOrder.h"
class AxonOrderLinear :public AxonOrder{
public:
    AxonManagerHandle makeAxonManager() override;
};


#endif //TUMORSIMULATION_AXONORDERLINEAR_H
