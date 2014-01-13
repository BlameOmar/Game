//
//  Component.h
//  Game
//
//  Created by Omar Stefan Evans on 12/7/13.
//
//

#ifndef __Game__Component__
#define __Game__Component__

#include "types.h"

namespace evansbros { namespace game { namespace engine {

    enum class ComponentType : natural {
        SPATIAL_COMPONENT,
        DRAWABLE_COMPONENT,
        COLIDABLE_COMPONENT
    };

    class Component {
    protected:
        ComponentType typeID;
        string typeString;
    public:
        ComponentType getTypeID() const;
        string getTypeString() const;

        virtual void update(seconds dTime) = 0;
    };
} } }

#endif /* defined(__Game__Component__) */
