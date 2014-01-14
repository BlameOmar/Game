//
//  natvie_utilities.cpp
//  OpenGL Practice
//
//  Created by Omar Evans on 7/24/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "native_utilities.h"
#import <Foundation/Foundation.h>
#import <Foundation/NSBundle.h>
#include "CGLRenderer.h"

using namespace evansbros;

const string getPathOfAssetDirectory()
{
    return string([[[[[NSBundle mainBundle] resourceURL] URLByAppendingPathComponent:@"assets" isDirectory:YES] path] UTF8String]);
}

const Data loadAsset(const string assetPath)
{
    NSURL *assetDirectoryURL = [[[NSBundle mainBundle] resourceURL] URLByAppendingPathComponent:@"assets" isDirectory:YES];
    NSURL *assetURL = [NSURL URLWithString:[NSString stringWithUTF8String:assetPath.c_str()] relativeToURL:assetDirectoryURL];
    NSData *nativeDataObject = [NSData dataWithContentsOfURL:assetURL];
    
    Data dataObject(nativeDataObject.length, (byte *)nativeDataObject.bytes);
    return dataObject;
}


evansbros::graphics::Renderer * getPlatformRenderer() {
    return new graphics::CGLRenderer;
}

evansbros::graphics::Renderer * getPlatformRenderer(graphics::RenderType hint) {
    return new graphics::CGLRenderer;
}