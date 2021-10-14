//
// Created by florian on 10/10/21.
//

#ifndef TUMORSIMULATION_BASEAXON_H
#define TUMORSIMULATION_BASEAXON_H


#include <vector>
#include "../../util/TypeDefs.h"

class ConstraintManager;

class EuclideanVector;

class BaseAxon {
protected:
    PositionList m_tipPositions;
    ConstraintManagerHandle m_constraintHandler;
    int m_identifier;
    bool m_active{true};

    static int m_currentIdentifier;

protected:

    BaseAxon(EuclideanVector startPosition, std::shared_ptr<ConstraintManager> constraintHandler);

    BaseAxon(EuclideanVector startPosition, EuclideanVector nextPosition,
             std::shared_ptr<ConstraintManager> constraintHandler);

public:
    void stopAxon();

    [[nodiscard]] virtual bool isActive() const;

    virtual void grow() {};

    PositionList getTipPositions();


};


#endif //TUMORSIMULATION_BASEAXON_H
