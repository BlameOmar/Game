/**************************************************************************************************
 * Title:         SpatialComponent.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "SpatialComponent.h"

namespace evansbros {
    namespace game {
        real SpatialComponent::speed() const
        {
            return velocity.magnitude();
        }
    }
}