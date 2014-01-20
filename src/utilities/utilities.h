/**************************************************************************************************
 * Title:         utilities.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-26
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "native_utilities.h"

#include "PixelData.h"

namespace evansbros {

    PixelData decodePNGData(const Data &data, bool shouldPremultiplyAlpha = true);

}