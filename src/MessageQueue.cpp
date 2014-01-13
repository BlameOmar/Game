/**
 * ©2013 Omar Stefan Evans.  All rights reserved.
 */

/**************************************************************************************************
 * Title:         MessageQueue.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-14
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "MessageQueue.h"

namespace evansbros { namespace game {

    MessageQueue::MessageQueue(size_t capacity) throw(std::domain_error) : size(capacity + 1), head(0), tail(0)
    {
        switch (size) {
            case 0:
                throw(std::domain_error("MessageQueue: capacity exceeds the platform limit"));
            case 1:
                throw(std::domain_error("MessageQueue: capacity must not be set to zero"));
            default:
                messages = new Message[size];
        }
    }

    MessageQueue::~MessageQueue()
    {
        delete [] messages;
    }

    void MessageQueue::enqueue(Message message)
    {
        if (wasFull()) {
            return;
        }

        auto current_tail = tail.load();
        messages[current_tail] = message;
        tail.store((current_tail + 1) % size);
    }

    Message MessageQueue::dequeue()
    {
        if (wasEmpty()) {
            return Message();
        }

        auto current_head = head.load();

        Message message = messages[current_head];
        head.store((current_head + 1) % size);
        return message;
    }

    bool MessageQueue::wasEmpty() const
    {
        return head.load() == tail.load();
    }

    bool MessageQueue::wasFull() const
    {
        return head.load() == (tail.load() + 1) % size;
    }

} }
