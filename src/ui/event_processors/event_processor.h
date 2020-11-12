#ifndef DEMO_EVENT_PROCESSOR_H
#define DEMO_EVENT_PROCESSOR_H

#include <ui/event.h>

class EventProcessor
{
public:
    virtual void process_event(const Event* event) = 0;
};

#endif // DEMO_EVENT_PROCESSOR_H
