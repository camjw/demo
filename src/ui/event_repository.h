#ifndef DEMO_EVENT_REPOSITORY_H
#define DEMO_EVENT_REPOSITORY_H

#include <queue>
#include <ui/event.h>
#include <ui/event_processors/event_processor.h>
#include <unordered_map>

class EventRepository
{
public:
    inline void update()
    {
        process_events();
    }

    inline void late_update()
    {
        process_events();
    }

    inline void add_event(const Event* event)
    {
        events_to_process.push(event);
    }

    inline void add_event_repository(const char* event_type, EventProcessor* event_processor)
    {
        if (event_processors.find(event_type) == event_processors.end())
        {
            event_processors.insert(std::pair<const char*, std::vector<EventProcessor*>>(event_type, {event_processor}));
        }
        else
        {
            event_processors.find(event_type)->second.push_back(event_processor);
        }
    }

private:
    void process_events();

private:
    std::queue<const Event*> events_to_process;
    std::unordered_map<const char*, std::vector<EventProcessor*>> event_processors;
};

#endif //DEMO_EVENT_REPOSITORY_H
