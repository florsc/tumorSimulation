//
// Created by florian on 10/19/21.
//

#ifndef TUMORSIMULATION_TARGETMANAGER_H
#define TUMORSIMULATION_TARGETMANAGER_H


#include <vector>
#include "../Targets/Target.h"
#include "../util/TypeDefs.h"

class TargetManager {
    TargetVector m_targets;
public:
    explicit TargetManager(TargetVector targets);

    bool checkTargetReached(const EuclideanVector &position);
};


#endif //TUMORSIMULATION_TARGETMANAGER_H
