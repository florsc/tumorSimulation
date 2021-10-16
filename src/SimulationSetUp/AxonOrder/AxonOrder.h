//
// Created by florian on 10/15/21.
//

#ifndef TUMORSIMULATION_AXONORDER_H
#define TUMORSIMULATION_AXONORDER_H

#include "../../util/TypeDefs.h"

class AxonOrder {
public:
    virtual AxonManagerHandle makeAxonManager() = 0;
};


#endif //TUMORSIMULATION_AXONORDER_H
