/**************************************************************************************************
 * @file    Component.cpp
 * @date    2014-04-02
 * @brief   Abstract Component Structure
 * @details <#Detailed Description#>
 **************************************************************************************************/

#include "Component.h"

namespace evansbros {
    namespace game {

        Component::Component(UniqueID entity_uid) : entity_uid(entity_uid) {}

        UniqueID Component::getUID() const {
            return uid;
        }

        UniqueID Component::getEntityUID() const {
            return entity_uid;
        }

    }
}