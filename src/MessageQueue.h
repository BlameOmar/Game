/**
 * ©2013 Omar Stefan Evans.  All rights reserved.
 */

/**************************************************************************************************
 * Title:         MessageQueue.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-14
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include <cstdlib>

#include <atomic>
#include <stdexcept>

#include "Message.h"

namespace evansbros { namespace game {

    class MessageQueue {
    private:
        const size_t size;
        Message *messages;

        std::atomic_size_t head;
        std::atomic_size_t tail;

    public:
        MessageQueue(size_t capacity);
        ~MessageQueue();

        MessageQueue(const MessageQueue & other) = delete;
        MessageQueue & operator=(const MessageQueue & other) = delete;

        void enqueue(Message message);
        Message dequeue();

        bool wasEmpty() const;
        bool wasFull() const;
    };

} }
