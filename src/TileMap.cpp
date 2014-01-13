/**************************************************************************************************
 * Title:         TileMap.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-04
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "TileMap.h"
#include <sstream>

namespace evansbros { namespace game {

    TileMap::TileMap() : width(20), height(14)
    {
        textureDefinitions[0] = "grass";
        textureDefinitions[1] = "dirt";
        textureDefinitions[2] = "cobblestone";
        textureDefinitions[3] = "water";
        textureDefinitions[4] = "sand";

        tiles = std::vector<natural> {
            0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            4, 4, 4, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            3, 3, 3, 4, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            3, 3, 3, 4, 1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            3, 3, 3, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 1, 4, 1, 4, 1, 0, 0,
            3, 3, 3, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 4, 1, 4, 1, 4, 0, 0,
            3, 3, 3, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 1, 4, 1, 4, 1, 0, 0,
            3, 3, 3, 4, 1, 0, 0, 0, 2, 2, 0, 0, 0, 4, 1, 4, 1, 4, 0, 0,
            3, 3, 4, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 4, 1, 4, 1, 0, 0,
            4, 4, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
    }

    natural & TileMap::operator() (natural i, natural j)
    {
        if (i >= width || j >= height) {
            std::ostringstream out;
            out << "(" << i << ", " << j << ") is not in the domain: "
            << "[0, " << width << ") X [0, " << height << ")\n";
            throw (std::domain_error(out.str()));
        }
        return tiles[j * width + i];
    }

    natural   TileMap::operator() (natural i, natural j) const
    {
        if (i >= width || j >= height) {
            std::ostringstream out;
            out << "(" << i << ", " << j << ") is not in Domain = "
            << "[0, " << width << ") X [0, " << height << ")\n";
            throw (std::domain_error(out.str()));
        }
        return tiles[j * width + i];
    }

} }