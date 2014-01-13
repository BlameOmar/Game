//
//  SpatialComponent.h
//  Game
//
//  Created by Omar Stefan Evans on 12/7/13.
//
//

#ifndef __Game__SpatialComponent__
#define __Game__SpatialComponent__

#include "Component.h"

#include "vector3.h"

using evansbros::math::vector3;

namespace evansbros { namespace game { namespace engine {

    class SpatialComponent : public Component {
    protected:
        ComponentType typeID = ComponentType::SPATIAL_COMPONENT;
        string typeString = "SpatialComponent";
    public:
        virtual void update(seconds dTime) override;

        vector3 getPosition() const;
        vector3 getVelocity() const;
    private:
        vector3 position;
        vector3 velocity;
    };

} } }

#endif /* defined(__Game__SpatialComponent__) */
