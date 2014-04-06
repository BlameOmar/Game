/**************************************************************************************************
 * Title:         Entity.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "Entity.h"

namespace evansbros {
    namespace game {
        UniqueID Entity::getUID() const {
            return uid;
        }
    }
}