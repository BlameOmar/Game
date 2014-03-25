/**************************************************************************************************
 * Title:         Entity.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"

namespace evansbros {
    namespace game {
        struct Entity {
            static ID next_id;

            ID id = 0;

            Entity() = default;
            Entity(ID id) : id(id) {}
        };
    }
}