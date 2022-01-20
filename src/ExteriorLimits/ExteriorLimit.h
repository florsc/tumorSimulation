//
// Created by florian on 9/17/21.
//

#ifndef TUMORSIMULATION_EXTERIORLIMIT_H
#define TUMORSIMULATION_EXTERIORLIMIT_H


#include <vector>
#include "../util/EuclideanVector.h"
#include "../util/TypeDefs.h"
#include <iostream>

class ExteriorLimit {
public:
    [[nodiscard]] virtual bool checkExteriorLimitExceeded(EuclideanVector) const = 0;
};

class SphericalLimit : public ExteriorLimit {
private:
    double m_radiusSquared;
public:
    explicit SphericalLimit(SphericalLimitSetUpParametersHandle sphericalLimitSetUpParametersHandle);

    [[nodiscard]] bool checkExteriorLimitExceeded(EuclideanVector position) const override;

};


#endif //TUMORSIMULATION_EXTERIORLIMITCHECKER_H
