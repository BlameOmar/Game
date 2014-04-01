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
        textureDefinitions[1] = "grass";
        textureDefinitions[2] = "dirt";
        textureDefinitions[3] = "cobblestone";
        textureDefinitions[4] = "water";
        textureDefinitions[5] = "sand";

        tiles = std::vector<natural> {
            1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            5, 5, 5, 2, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            4, 4, 4, 5, 2, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            4, 4, 4, 5, 2, 2, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            4, 4, 4, 4, 5, 2, 1, 1, 3, 3, 1, 1, 1, 2, 5, 2, 5, 2, 1, 1,
            4, 4, 4, 4, 5, 2, 1, 1, 3, 3, 1, 1, 1, 5, 2, 5, 2, 5, 1, 1,
            4, 4, 4, 4, 5, 2, 1, 1, 3, 3, 1, 1, 1, 2, 5, 2, 5, 2, 1, 1,
            4, 4, 4, 5, 2, 1, 1, 1, 3, 3, 1, 1, 1, 5, 2, 5, 2, 5, 1, 1,
            4, 4, 5, 2, 1, 1, 1, 1, 3, 3, 1, 1, 1, 2, 5, 2, 5, 2, 1, 1,
            5, 5, 2, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
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