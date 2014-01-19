//
//  data.cpp
//  OpenGL Practice
//
//  Created by Omar Evans on 7/24/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "Data.h"

namespace evansbros {

    Data::Data(size_t size, void *bytes) : size(size) {
        this->bytes = std::shared_ptr<void>(new byte[size], std::default_delete<byte[]>());

        memcpy(this->bytes.get(), bytes, size);
    }


    const void * Data::getBytes() const
    {
        return bytes.get();
    }

    size_t Data::getSize() const
    {
        return size;
    }
    
}
