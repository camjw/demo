#ifndef DEMO_NAME_COMPONENT_H
#define DEMO_NAME_COMPONENT_H

struct NameComponent
{
    std::string name;
};

REGISTER_COMPONENT(Name, NameComponent)

#endif // DEMO_NAME_COMPONENT_H
