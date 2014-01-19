//
//  PixelData.h
//  OpenGL Practice
//
//  Created by Omar Evans on 7/30/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#pragma once

#include "types.h"
#include "Data.h"

namespace evansbros {
    enum class PixelChannelOrder : byte {
        UNKNOWN          = 0,   UNKNOWN_ORDER = 0,
        ARGB = 1,   BGRA = 1,   BGRA_ORDER    = 1,
        RGBA = 2,               RGBA_ORDER    = 2
    };

    enum class PixelChannelName : byte {
        R = 0,  RED   = 0,   RED_CHANNEL   = 0,
        G = 1,  GREEN = 1,   GREEN_CHANNEL = 1,
        B = 2,  BLUE  = 2,   BLUE_CHANNEL  = 2,
        A = 3,  ALPHA = 3,   ALPHA_CHANNEL = 3
    };

    enum class PixelChannelType : byte {
        INTEGER,
        UNSIGNED_INTEGER,
        FLOAT
    };

    struct PixelChannel {
        PixelChannelName    name;
        PixelChannelType    type;
        natural_8bit        numberOfBits;
    };

    struct PixelFormat {
        natural_8bit        numberOfChannels;
        std::shared_ptr<PixelChannel> channels;

        PixelFormat() : PixelFormat(0, nullptr) {}
        PixelFormat(natural_8bit numberOfChannels, const PixelChannel *channels) : numberOfChannels(numberOfChannels), channels(new PixelChannel[numberOfChannels], std::default_delete<PixelChannel[]>()) {
            for (int i = 0; i < numberOfChannels; ++i) {
                this->channels.get()[i] = channels[i];
            }
        }
        PixelFormat(PixelFormat const &other) : PixelFormat(other.numberOfChannels, other.channels.get()) {}
        bool hasAlpha();
        PixelChannelOrder getChannelOrder();
    };

    class PixelData {
        natural width;
        natural height;
        PixelFormat pixelFormat;
        Data pixelData;
    public:
        PixelData() : PixelData(0, 0, PixelFormat(), Data()) {}
        PixelData(natural width, natural height, PixelFormat pixelFormat, Data pixelData) : width(width), height(height), pixelFormat(pixelFormat), pixelData(pixelData) {}
        PixelData(const PixelData &other) : PixelData(other.width, other.height, other.pixelFormat, other.pixelData) {}
        
        natural getWidth() const;
        natural getHeight() const;
        const PixelFormat getPixelFormat() const;
        const void *getBytes() const;
    };

}

