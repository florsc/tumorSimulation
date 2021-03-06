//
// Created by florian on 9/30/21.
//

#include "AxonManager.h"
#include "../../Axons/AxonTypes/BaseAxon/BaseAxon.h"

void AxonManager::removeAxon(int id) {
    m_allAxons.erase(std::find_if(m_allAxons.begin(), m_allAxons.end(), [&](const AxonHandle &axon) {
        return axon->hasId(id);
    }));
}
