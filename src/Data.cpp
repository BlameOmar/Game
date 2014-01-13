//
//  data.cpp
//  OpenGL Practice
//
//  Created by Omar Evans on 7/24/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "Data.h"

namespace evansbros {

    Data::Data(size_t size, byte *bytes) : size(size) {
        this->bytes = std::shared_ptr<byte>(new byte[size], std::default_delete<byte[]>());

        for (int i = 0; i < size; ++i) {
            this->bytes.get()[i] = bytes[i];
        }
    }


    const byte * Data::getBytes() const
    {
        return bytes.get();
    }

    size_t Data::getSize() const
    {
        return size;
    }
    
}
