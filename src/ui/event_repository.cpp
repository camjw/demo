#include "event_repository.h"
#include <ui/event_processors/event_processor.h>

void EventRepository::process_events() {
    while (!events_to_process.empty())
    {
        const Event* next_event = events_to_process.front();
        const char* event_type = next_event->get_type();

        auto event_processors_for_event_type = event_processors.find(event_type);

        if (event_processors_for_event_type != event_processors.end())
        {
           for (int i = 0; i < event_processors_for_event_type->second.size(); i++)
           {
               event_processors_for_event_type->second[i]->process_event(next_event);
           }
        }

        events_to_process.pop();
    }
}