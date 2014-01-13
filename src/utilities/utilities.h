//
//  utilities.h
//  OpenGL Practice
//
//  Created by Omar Evans on 7/26/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__utilities__
#define __OpenGL_Practice__utilities__

#include "native_utilities.h"

#include "PixelData.h"

namespace evansbros {

    PixelData decodePNGData(const Data &data, bool shouldPremultiplyAlpha = true);

}

#endif /* defined(__OpenGL_Practice__utilities__) */
