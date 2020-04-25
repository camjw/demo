#ifndef DEMO_ECS_COMPONENT_MANAGER_HPP
#define DEMO_ECS_COMPONENT_MANAGER_HPP

#include <typeinfo>

#include <demo/ecs/component_array.hpp>
#include <demo/ecs/ecs.hpp>

class ComponentManager
{
public:
    template <typename T>
    void register_component()
    {
        const char* type_name = typeid(T).name();
        assert(componentTypes.find(type_name) == componentTypes.end() && "Registering component type more than once.");

        componentTypes.insert({ type_name, nextComponentType });

        componentArrays.insert({ type_name, std::make_shared<ComponentArray<T>>() });

        ++nextComponentType;
    }

    template <typename T>
    ComponentType get_component_type()
    {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

        return componentTypes[typeName];
    }

    template <typename T>
    void add_component(Entity entity, T component)
    {
        get_component_array<T>()->InsertData(entity, component);
    }

    template <typename T>
    void remove_component(Entity entity)
    {
        get_component_array<T>()->RemoveData(entity);
    }

    template <typename T>
    T& get_component(Entity entity)
    {
        return get_component_array<T>()->get_data(entity);
    }

    void on_entity_destroyed(Entity entity)
    {
        for (auto const& pair : componentArrays)
        {
            auto const& component = pair.second;

            component->on_entity_destroyed(entity);
        }
    }

private:
    std::unordered_map<const char*, ComponentType> componentTypes {};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays {};
    ComponentType nextComponentType {};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> get_component_array()
    {
        const char* typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};

#endif
