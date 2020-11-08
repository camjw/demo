#ifndef DEMO_EVENT_PROCESSOR_H
#define DEMO_EVENT_PROCESSOR_H

#include <input/event_processors/processable_event.h>
#include <queue>

class EventRepository
{
public:
    void process_events();
    void add_event();

private:
    std::queue<ProcessableEvent> events_to_process;
};

#endif //DEMO_EVENT_PROCESSOR_H
