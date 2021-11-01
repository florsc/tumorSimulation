//
// Created by florian on 9/13/21.
//

#ifndef TUMORSIMULATION_HELPERFUNCTIONS_H
#define TUMORSIMULATION_HELPERFUNCTIONS_H

#include <vector>
#include "EuclideanVector.h"
#include "../SimulationSetUp/ParameterStruct.h"

namespace HelperFunctions {

    EuclideanVector sph2cart(double az, double el, double r);

    bool
    checkForDirectionSimilarity(const EuclideanVector &oldVector, const EuclideanVector &newVector, double threshold);

    std::vector<EuclideanVector>
    createCoveringCenters(const EuclideanVector &start, const EuclideanVector &diff, double minDistance);

    template<typename Container>
    void removeElementsFromEnd(Container &container, int numberOfElementsToRemove) {
        container.erase(std::next(container.end(), -numberOfElementsToRemove),
                        container.end());
    }

    std::pair<double, double> getSphericalAngles(const EuclideanVector &v);

    std::pair<double, double> getModelParameters(const EuclideanVector &v);
};

#endif //TUMORSIMULATION_HELPERFUNCTIONS_H
