//
//  natvie_utilities.h
//  OpenGL Practice
//
//  Created by Omar Evans on 7/24/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__native_utilities__
#define __OpenGL_Practice__native_utilities__

#include "Data.h"
#include "Renderer.h"

using namespace evansbros;

const string getPathOfAssetDirectory();
const Data loadAsset(const string assetPath);
evansbros::graphics::Renderer * getPlatformRenderer();
evansbros::graphics::Renderer * getPlatformRenderer(evansbros::graphics::RenderType hint);

#endif /* defined(__OpenGL_Practice__natvie_utilities__) */
