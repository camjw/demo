#ifndef DEMO_ECS_COMPONENT_MANAGER_HPP
#define DEMO_ECS_COMPONENT_MANAGER_HPP

#include <typeinfo>

#include <ecs/component_array.h>
#include <ecs/ecs.h>

class ComponentManager
{
public:
    template <typename T>
    void register_component()
    {
        const char* type_name = typeid(T).name();
        assert(component_types.find(type_name) == component_types.end() && "Registering component type more than once.");

        component_types.insert({ type_name, next_component_type });

        component_arrays.insert({ type_name, std::make_shared<ComponentArray<T>>() });

        ++next_component_type;
    }

    template <typename T>
    ComponentType get_component_type()
    {
        const char* typeName = typeid(T).name();

        assert(component_types.find(typeName) != component_types.end() && "Component not registered before use.");

        return component_types[typeName];
    }

    template <typename T>
    void add_component(Entity entity, T component)
    {
        get_component_array<T>()->insert_data(entity, component);
    }

    template <typename T>
    void remove_component(Entity entity)
    {
        get_component_array<T>()->remove_data(entity);
    }

    template <typename T>
    T& get_component(Entity entity)
    {
        return get_component_array<T>()->get_data(entity);
    }

    template <typename T>
    bool has_component(Entity entity)
    {
        return get_component_array<T>()->has_data(entity);
    }

    void on_entity_destroyed(Entity entity)
    {
        for (auto const& pair : component_arrays)
        {
            auto const& component = pair.second;

            component->on_entity_destroyed(entity);
        }
    }

    bool has_component_registered(const char* component_name)
    {
        return component_types.find(component_name) != component_types.end();
    }

private:
    std::unordered_map<const char*, ComponentType> component_types {};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> component_arrays {};
    ComponentType next_component_type {};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> get_component_array()
    {
        const char* typeName = typeid(T).name();

        assert(component_types.find(typeName) != component_types.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(component_arrays[typeName]);
    }
};

#endif
