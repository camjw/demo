#ifndef DEMO_EVENT_H
#define DEMO_EVENT_H

class Event
{
public:
    virtual ~Event() {};
    virtual const char* get_type() const = 0;
};

#endif // DEMO_EVENT_H
