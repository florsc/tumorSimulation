//
// Created by florian on 9/17/21.
//

#ifndef TUMORSIMULATION_EXTERIORLIMIT_H
#define TUMORSIMULATION_EXTERIORLIMIT_H


#include <vector>
#include "../util/EuclideanVector.h"
#include <iostream>

class ExteriorLimit {
public:
    virtual bool checkExteriorLimitExceeded(EuclideanVector) const = 0;

    virtual ~ExteriorLimit() { std::cout << "Exterior Limit destructed" << std::endl; }
};

class SphericalLimit : public ExteriorLimit {
private:
    double m_radiusSquared;
public:
    SphericalLimit(double radius);

    bool checkExteriorLimitExceeded(EuclideanVector position) const override;

    ~SphericalLimit() { std::cout << "Spherical Limit destructed" << std::endl; }

};


#endif //TUMORSIMULATION_EXTERIORLIMITCHECKER_H
