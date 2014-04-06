/**************************************************************************************************
 * @file    ComponentManager.cpp
 * @date    2014-04-03
 * @brief   Manages Subclasses of Component
 * @details <#Detailed Description#>
 **************************************************************************************************/


#include "ComponentManager.h"

namespace evansbros {
    namespace game {
        UniqueID ComponentManager::nextUID = 0;

        void ComponentManager::removeComponent(UniqueID uid) {
            if (removeFunctionLookupTable.count(uid) == 0) {
                throw std::runtime_error("The specified component could not be found");
            }
            auto removeFunction = removeFunctionLookupTable[uid];
            removeFunction(uid);
        }
    }
}