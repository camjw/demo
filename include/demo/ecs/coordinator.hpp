#ifndef DEMO_ECS_COORDINATOR_HPP
#define DEMO_ECS_COORDINATOR_HPP

#include <demo/ecs/component_manager.hpp>
#include <demo/ecs/ecs.hpp>
#include <demo/ecs/entity_manager.hpp>
#include <demo/ecs/system_manager.hpp>

class Coordinator
{
public:
    void init()
    {
        // Create pointers to each manager
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
        systemManager = std::make_unique<SystemManager>();
    }

    // Entity methods
    Entity create_entity()
    {
        return entityManager->create_entity();
    }

    void destroy_entity(Entity entity)
    {
        entityManager->destroy_entity(entity);

        componentManager->on_entity_destroyed(entity);

        systemManager->on_entity_destroyed(entity);
    }

    // Component methods
    template <typename T>
    void register_component()
    {
        componentManager->register_component<T>();
    }

    template <typename T>
    void add_component(Entity entity, T component)
    {
        componentManager->add_component<T>(entity, component);

        auto signature = entityManager->get_signature(entity);
        signature.set(componentManager->get_component_type<T>(), true);
        entityManager->set_signature(entity, signature);

        systemManager->on_entity_signature_changed(entity, signature);
    }

    template <typename T>
    void remove_component(Entity entity)
    {
        componentManager->remove_component<T>(entity);

        auto signature = entityManager->get_signature(entity);
        signature.set(componentManager->get_component_type<T>(), false);
        entityManager->set_signature(entity, signature);

        systemManager->on_entity_signature_changed(entity, signature);
    }

    template <typename T>
    T& get_component(Entity entity)
    {
        return componentManager->get_component<T>(entity);
    }

    template <typename T>
    ComponentType get_component_type()
    {
        return componentManager->get_component_type<T>();
    }

    // System methods
    template <typename T>
    std::shared_ptr<T> register_system()
    {
        return systemManager->register_system<T>();
    }

    template <typename T>
    std::shared_ptr<T> register_updatable_system()
    {
        return systemManager->register_updatable_system<T>();
    }

    template <typename T>
    void set_system_signature(Signature signature)
    {
        systemManager->set_signature<T>(signature);
    }

private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
};

#endif
