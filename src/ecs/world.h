#ifndef DEMO_ECS_WORLD_HPP
#define DEMO_ECS_WORLD_HPP

#include <ecs/component_manager.h>
#include <ecs/ecs.h>
#include <ecs/entity_manager.h>
#include <ecs/system_manager.h>
#include <type_traits>

class SignatureBuilder;
class EntityBuilder;

class World
{
public:
    void init(std::shared_ptr<World> self)
    {
        // Create pointers to each manager
        component_manager = std::make_unique<ComponentManager>();
        entity_manager = std::make_unique<EntityManager>();
        system_manager = std::make_unique<SystemManager>();

        this->self = self;
    }

    // Entity methods
    Entity create_empty_entity()
    {
        return entity_manager->create_entity();
    }

    EntityBuilder* create_entity();

    void destroy_entity(Entity entity)
    {
        entity_manager->destroy_entity(entity);

        component_manager->on_entity_destroyed(entity);

        system_manager->on_entity_destroyed(entity);
    }

    // Component methods
    template <typename T>
    void register_component()
    {
        component_manager->register_component<T>();
    }

    template <typename T>
    void add_component(Entity entity, T component)
    {
        component_manager->add_component<T>(entity, component);

        auto signature = entity_manager->get_signature(entity);
        signature.set(component_manager->get_component_type<T>(), true);
        entity_manager->set_signature(entity, signature);

        system_manager->on_entity_signature_changed(entity, signature);
    }

    template <typename T>
    void remove_component(Entity entity)
    {
        component_manager->remove_component<T>(entity);

        auto signature = entity_manager->get_signature(entity);
        signature.set(component_manager->get_component_type<T>(), false);
        entity_manager->set_signature(entity, signature);

        system_manager->on_entity_signature_changed(entity, signature);
    }

    template <typename T>
    T& get_component(Entity entity)
    {
        return component_manager->get_component<T>(entity);
    }

    template <class T>
    T& get_or_add_component(Entity entity, T& value)
    {
        if (has_component<T>(entity))
        {
            get_component<T>(entity) = value;
        }
        else
        {
            add_component<T>(entity, value);
        }

        return value;
    }

    template <typename T>
    bool has_component(Entity entity)
    {
        return component_manager->has_component<T>(entity);
    }

    template <typename T>
    ComponentType get_component_type()
    {
        return component_manager->get_component_type<T>();
    }

    // System methods
    template <typename T>
    std::shared_ptr<T> register_system()
    {
        return system_manager->register_system<T>(this);
    }

    template <typename T>
    std::shared_ptr<T> register_system(T& system)
    {
        return system_manager->register_system<T>(system, this);
    }

    template <typename T>
    void set_system_signature(Signature signature)
    {
        system_manager->set_signature<T>(signature);
    }

    void update_systems(Time time, InputState* input)
    {
        system_manager->update_systems(time, input);
    }

    void late_update_systems(Time time, InputState* input)
    {
        system_manager->late_update_systems(time, input);
    }

    std::vector<Entity> get_entities_with_signature(Signature signature)
    {
        return entity_manager->get_entities_with_signature(signature);
    }

    bool has_component_registered(const char* component_name)
    {
        return component_manager->has_component_registered(component_name);
    }

    SignatureBuilder get_signature_builder();

private:
    std::unique_ptr<ComponentManager> component_manager;
    std::unique_ptr<EntityManager> entity_manager;
    std::unique_ptr<SystemManager> system_manager;

    std::shared_ptr<World> self;
};

using component_registration_function = void (*)(std::shared_ptr<World> world);
void register_component(component_registration_function crf);
static std::vector<component_registration_function>& components_to_register();

using system_registration_function = void (*)(std::shared_ptr<World> world, Signature signature);
void register_system(system_registration_function srf);
static std::vector<system_registration_function>& systems_to_register()
{
    static std::vector<system_registration_function> v;
    return v;
}

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define CONCAT3(a, b, c) CONCAT(a, CONCAT(b, c))

// ComponentName should be globally unique (can get lucky if they repeat),
// but they don't have any other impact.
#define REGISTER_COMPONENT(ComponentName, ComponentType)                                              \
    static_assert(std::is_class<ComponentType>::value, "Must pass type in");                          \
    namespace detail                                                                                  \
    {                                                                                                 \
        /* function we later define */                                                                \
        static void CONCAT3(ComponentName, _registered_fun_, __LINE__)(std::shared_ptr<World> world); \
                                                                                                      \
        namespace /* ensure internal linkage for struct */                                            \
        {                                                                                             \
            /* helper struct for static registration in ctor */                                       \
            struct CONCAT3(ComponentName, _register_struct_, __LINE__)                                \
            {                                                                                         \
                CONCAT3(ComponentName, _register_struct_, __LINE__)                                   \
                ()                                                                                    \
                { /* called once before main */                                                       \
                    register_component(CONCAT3(ComponentName, _registered_fun_, __LINE__));           \
                }                                                                                     \
            } CONCAT3(ComponentName, _register_struct_instance_, __LINE__);                           \
        }                                                                                             \
    }                                                                                                 \
    void detail::CONCAT3(ComponentName, _registered_fun_, __LINE__)(std::shared_ptr<World> world)     \
    {                                                                                                 \
        world->register_component<ComponentType>();                                                   \
    }

#endif
