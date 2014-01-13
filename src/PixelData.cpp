//
//  ImageData.cpp
//  OpenGL Practice
//
//  Created by Omar Evans on 7/30/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "ImageData.h"

natural ImageData::getWidth() const
{
    return width;
}

natural ImageData::getHeight() const
{
    return height;
}

const PixelFormat ImageData::getPixelFormat() const
{
    return pixelFormat;
}

const byte * ImageData::getBytes() const
{
    return pixelData.getBytes();
}

bool PixelFormat::hasAlpha()
{
    for (natural_8bit i = 0; i < numberOfChannels; ++i) {
        if (channels.get()[i].name == PixelChannelName::ALPHA) {
            return true;
        }
    }
    
    return false;
}

PixelChannelOrder PixelFormat::getChannelOrder() {
    if (channels.get()[0].name == PixelChannelName::RED   &&
        channels.get()[1].name == PixelChannelName::GREEN &&
        channels.get()[2].name == PixelChannelName::BLUE  &&
        channels.get()[3].name == PixelChannelName::ALPHA) {
        return PixelChannelOrder::RGBA;
    } else if (channels.get()[0].name == PixelChannelName::BLUE  &&
               channels.get()[1].name == PixelChannelName::GREEN &&
               channels.get()[2].name == PixelChannelName::RED   &&
               channels.get()[3].name == PixelChannelName::ALPHA) {
        return PixelChannelOrder::BGRA;
    } else {
        return PixelChannelOrder::UNKNOWN;
    }
}