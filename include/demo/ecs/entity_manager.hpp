#ifndef DEMO_ECS_ENTITY_MANAGER_HPP
#define DEMO_ECS_ENTITY_MANAGER_HPP

#include <demo/ecs/ecs.h>

#include <array>
#include <queue>

class EntityManager
{
    public:
        EntityManager()
        {
            for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
            {
                availableEntities.push(entity);
            }
        }

        Entity create_entity()
        {
            assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

            Entity id = availableEntities.front();
            availableEntities.pop();
            ++livingEntityCount;

            return id;
        }

        void destroy_entity(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity].reset();

            availableEntities.push(entity);
            --livingEntityCount;
        }

        void set_signature(Entity entity, Signature signature)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity] = signature;
        }

        Signature get_signature(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            return signatures[entity];
        }

    private:
        std::queue<Entity> availableEntities;
        std::array<Signature, MAX_ENTITIES> signatures;
        uint32_t livingEntityCount = 0;
};

#endif
