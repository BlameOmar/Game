/**************************************************************************************************
 * Title:         TileMap.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-04
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "types.h"
#include <map>
#include <vector>


namespace evansbros { namespace game {

    struct TileMap {
        natural width;
        natural height;

        std::map<natural, string> textureDefinitions;
        std::vector<natural> tiles;

        TileMap();

        natural & operator() (natural i, natural j);
        natural   operator() (natural i, natural j) const;
    };

} }