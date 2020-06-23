#ifndef DEMO_ECS_SYSTEM_MANAGER_HPP
#define DEMO_ECS_SYSTEM_MANAGER_HPP

#include <typeinfo>
#include <unordered_map>

#include <ecs/ecs.h>
#include <ecs/system.h>

#include <input_processor.h>
#include <timer.h>

class SystemManager
{
public:
    template <typename T>
    std::shared_ptr<T> register_system(World* world)
    {
        const char* typeName = typeid(T).name();

        assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        auto system_ptr = std::make_shared<T>(std::move(T(world)));
        systems.insert({ typeName, system_ptr });
        return system_ptr;
    }

    template <typename T>
    std::shared_ptr<T> register_system(const T& system, World* world)
    {
        const char* typeName = typeid(T).name();

        assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        system.set_world(world);
        auto system_ptr = std::make_shared<T>(std::move(system));
        systems.insert({ typeName, system_ptr });
        return system_ptr;
    }

    template <typename T>
    void set_signature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(systems.find(typeName) != systems.end() && "System used before registered.");

        // Set the signature for this system
        signatures.insert({ typeName, signature });
    }

    void on_entity_destroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // entities is a set so no check needed
        for (auto const& pair : systems)
        {
            auto const& system = pair.second;

            system->entities.erase(entity);
        }
    }

    void on_entity_signature_changed(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (auto const& pair : systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->entities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                system->entities.erase(entity);
            }
        }
    }

    void update_systems(Time time, InputState* input)
    {
        for (auto const& system : systems)
        {
            system.second->update(time, input);
        }
    }

    void late_update_systems(Time time, InputState* input)
    {
        for (auto const& system : systems)
        {
            system.second->late_update(time, input);
        }
    }

private:
    std::unordered_map<const char*, Signature> signatures {};
    std::unordered_map<const char*, std::shared_ptr<System>> systems {};
};

#endif
