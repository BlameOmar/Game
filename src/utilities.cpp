//
//  utilities.cpp
//  OpenGL Practice
//
//  Created by Omar Evans on 7/26/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "utilities.h"
#include "png.h"

ImageData decodePNGData(const Data &data, bool shouldPremultiplyAlpha) {
    png_image image;
    memset(&image, 0, (sizeof image));
    image.version = PNG_IMAGE_VERSION;
    
    if (!png_image_begin_read_from_memory(&image, (void *)data.getBytes(), data.getSize())) {
        throw std::runtime_error("Not PNG data");
    }
    
    /*
     * According to the example.c file for version 1.6 of libpng, converting 8 bit images to
     * 16 bit images is currently lossy. However, the reverse is hopelessly lossy.  It is
     * also useful to have linear RGB values to correctly premultiply the alpha channel.
     * Therefore all PNG data will be interpreted as 16 bit images, no exceptions.
     */
    image.format = PNG_FORMAT_LINEAR_RGB_ALPHA;
    
    png_size_t bufferSize = PNG_IMAGE_SIZE(image);
    png_byte *buffer = new png_byte[bufferSize];
    if (buffer == nullptr) {
        throw std::runtime_error("Out of memeory");
    }
    
    png_image_finish_read(&image, NULL/*background*/, buffer, 0/*row_stride*/, NULL/*colormap*/);
    
    /*
     * PNGs are internally stored with non-premultiplied alpha channels.  It is often more
     * useful for their values to be premultiplied.  Since the PNG data was interpreted as
     * a 16 bit image, the byte array must be reinterpreted as an array of 16 bit natural
     * numbers.
     */
    if (shouldPremultiplyAlpha) {
        natural_16bit *pixels = reinterpret_cast<natural_16bit *>(buffer);
        for (unsigned int i = 0; i < bufferSize / sizeof(natural_16bit); i += 4) {
            pixels[i + 0] *= pixels[i + 3] / float(0xFFFF);
            pixels[i + 1] *= pixels[i + 3] / float(0xFFFF);
            pixels[i + 2] *= pixels[i + 3] / float(0xFFFF);
        }
    }
    
    natural_8bit numberOfBitsPerChannel = 16;
    PixelChannel channels[] {{PixelChannelName::RED, PixelChannelType::UNSIGNED_INTEGER, numberOfBitsPerChannel},
                              {PixelChannelName::GREEN, PixelChannelType::UNSIGNED_INTEGER, numberOfBitsPerChannel},
                              {PixelChannelName::BLUE, PixelChannelType::UNSIGNED_INTEGER, numberOfBitsPerChannel},
                              {PixelChannelName::ALPHA, PixelChannelType::UNSIGNED_INTEGER, numberOfBitsPerChannel},
    };
    PixelFormat format {sizeof(channels) / sizeof(PixelChannel), channels};
    ImageData imageData {image.width, image.height, format, Data(bufferSize, buffer)};
    
    delete [] buffer;
    
    return imageData;
}