#ifndef DEMO_ECS_ENTITY_MANAGER_HPP
#define DEMO_ECS_ENTITY_MANAGER_HPP

#include <ecs/ecs.h>

#include <array>
#include <memory>
#include <queue>

class EntityManager
{
public:
    EntityManager(std::array<Signature, MAX_ENTITIES> signatures): signatures(signatures)
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
        {

            available_entities.push(entity);
        }
    }

    Entity create_entity()
    {
        assert(living_entity_count < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = available_entities.front();
        available_entities.pop();

        living_entities[living_entity_count] = id;
        entity_positions[id] = living_entity_count++;

        return id;
    }

    void destroy_entity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures[entity].reset();

        available_entities.push(entity);

        // okay so say entity 4 is at position 2 and there are 5 entities
        // then living_entities = [0, 4, 6, 2, 7]
        // and entity_positions = [0, 10, 3, 9, 1, 8, 2, 4, 7, 6, 5]  11 entities total

        // should become living_entities = [0, 7, 6, 2]
        // should become entity_positions = [0, 10, 3, 9, 4, 8, 2, 1, 7, 6, 5]  11 entities total

        // living_entity_count = 5
        // we delete entity 4, so then living_entities should become
        // [0, 7, 6, 2]

        // Swap living entity to back of array
        uint32_t entity_position = entity_positions[entity];
        living_entities[entity_position] = living_entities[living_entity_count - 1];
        entity_positions[living_entities[living_entity_count - 1]] = entity_position;

        living_entity_count--;
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

    std::vector<Entity> get_entities_with_signature(Signature signature)
    {
        std::vector<Entity> output;
        for (int i = 0; i < living_entity_count; i++)
        {
            Signature entity_signature = signatures[living_entities[i]];
            if ((entity_signature & signature) == signature)
            {
                output.push_back(living_entities[i]);
            }
        }

        return output;
    }

    std::vector<Entity> get_entities_with_exact_signature(Signature signature)
    {
        std::vector<Entity> output;
        for (int i = 0; i < living_entity_count; i++)
        {
            Signature entity_signature = signatures[living_entities[i]];
            if (entity_signature == signature)
            {
                output.push_back(living_entities[i]);
            }
        }

        return output;
    }

private:
    std::queue<Entity> available_entities;
    std::array<Entity, MAX_ENTITIES> living_entities;
    // This gives us the index of the entity in the living_entities array
    std::array<uint32_t, MAX_ENTITIES> entity_positions;

    std::array<Signature, MAX_ENTITIES> signatures;

    uint32_t living_entity_count = 0;
};

#endif
