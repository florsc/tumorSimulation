//
// Created by florian on 10/19/21.
//

#include "TargetManager.h"

#include <utility>

TargetManager::TargetManager(TargetVector targets) : m_targets(std::move(targets)) {}

bool TargetManager::checkTargetReached(const EuclideanVector &position) {
    bool reached = false;
    for (const auto &target: m_targets) {
        if (target->checkTargetReached(position)) {
            reached = true;
            break;
        }
    }
    return reached;
}
