//
//  data.h
//  OpenGL Practice
//
//  Created by Omar Evans on 7/24/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__data__
#define __OpenGL_Practice__data__

#include <memory>

#include "types.h"

namespace evansbros {

    class Data {
    private:
        size_t size = 0;
        std::shared_ptr<void> bytes = nullptr;

    public:
        Data()                                  = default;
        Data(Data const &other)                 = default;
        Data & operator=(const Data & other)    = default;
        ~Data()                                 = default;

        Data(size_t size, void *bytes);

        size_t getSize() const;
        const void * getBytes() const;
    };
    
}

#endif /* defined(__OpenGL_Practice__data__) */
