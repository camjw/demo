#ifndef DEMO_EVENT_PROCESSOR_H
#define DEMO_EVENT_PROCESSOR_H

class EventProcessor
{
    virtual void process_event(ProcessableEvent event) = 0;
};

#endif // DEMO_EVENT_PROCESSOR_H
