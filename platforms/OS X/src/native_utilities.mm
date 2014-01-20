/**************************************************************************************************
 * Title:         native_utilities.mm
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-24
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

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