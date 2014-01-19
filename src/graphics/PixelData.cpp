//
//  PixelData.cpp
//  OpenGL Practice
//
//  Created by Omar Evans on 7/30/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "PixelData.h"

namespace evansbros {

    natural PixelData::getWidth() const
    {
        return width;
    }

    natural PixelData::getHeight() const
    {
        return height;
    }

    const PixelFormat PixelData::getPixelFormat() const
    {
        return pixelFormat;
    }

    const void * PixelData::getBytes() const
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

}
