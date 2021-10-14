//
// Created by florian on 9/17/21.
//

#ifndef TUMORSIMULATION_EXTERIORLIMIT_H
#define TUMORSIMULATION_EXTERIORLIMIT_H


#include <vector>
#include "../util/EuclideanVector.h"

class ExteriorLimit {
public:
    virtual bool checkExteriorLimitExceeded(EuclideanVector) = 0;
};

class SphericalLimit : public ExteriorLimit {
private:
    double m_radiusSquared;
public:
    SphericalLimit(double radius);

    bool checkExteriorLimitExceeded(EuclideanVector position) override;

};


#endif //TUMORSIMULATION_EXTERIORLIMITCHECKER_H
