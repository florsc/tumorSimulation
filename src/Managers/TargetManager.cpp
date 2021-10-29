//
// Created by florian on 10/19/21.
//

#include "TargetManager.h"

#include <utility>

TargetManager::TargetManager(TargetVector targets) : m_targets(std::move(targets)) {}

bool TargetManager::checkTargetReached(const EuclideanVector &position)  const{
    bool reached = false;
    for (const auto &target: m_targets) {
        if (target->checkTargetReached(position)) {
            reached = true;
            break;
        }
    }
    return reached;
}

EuclideanVector TargetManager::calculateForce(const EuclideanVector &position) const {
    auto force = EuclideanVector();
    for(const auto& target:m_targets){
        force += target->calculateForce(position);
    }
    return force;
}

