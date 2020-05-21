#ifndef DEMO_ACTION_H
#define DEMO_ACTION_H

#include <memory>

template <class T>
class Action
{
public:
    virtual void run(std::shared_ptr<T> entity) = 0;
};

#endif // DEMO_ACTION_H
