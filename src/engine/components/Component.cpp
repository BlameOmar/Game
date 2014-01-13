//
//  Component.cpp
//  Game
//
//  Created by Omar Stefan Evans on 12/7/13.
//
//

#include "Component.h"

namespace evansbros { namespace game { namespace engine {

    ComponentType Component::getTypeID() const
    {
        return typeID;
    }
    
    string Component::getTypeString() const
    {
        return typeString;
    }

} } }
