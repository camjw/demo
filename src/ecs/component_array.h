#ifndef DEMO_ECS_COMPONENT_ARRAY_HPP
#define DEMO_ECS_COMPONENT_ARRAY_HPP

#include <demo/ecs/ecs.h>

#include <unordered_map>

class IComponentArray
{
public:
    virtual ~IComponentArray() {};
    virtual void on_entity_destroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
    ~ComponentArray() {};

    void insert_data(Entity entity, T component)
    {
        assert(entity_to_index_map.find(entity) == entity_to_index_map.end() && "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t newIndex = mSize;
        entity_to_index_map[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        componentArray[newIndex] = component;
        ++mSize;
    }

    void remove_data(Entity entity)
    {
        assert(entity_to_index_map.find(entity) != entity_to_index_map.end() && "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = entity_to_index_map[entity];
        size_t indexOfLastElement = mSize - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
        entity_to_index_map[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        entity_to_index_map.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        --mSize;
    }

    T& get_data(Entity entity)
    {
        assert(entity_to_index_map.find(entity) != entity_to_index_map.end() && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return componentArray[entity_to_index_map[entity]];
    }

    bool has_data(Entity entity)
    {
        return entity_to_index_map.find(entity) != entity_to_index_map.end();
    }

    void on_entity_destroyed(Entity entity) override
    {
        if (entity_to_index_map.find(entity) != entity_to_index_map.end())
        {
            remove_data(entity);
        }
    }

private:
    std::array<T, MAX_ENTITIES> componentArray;
    std::unordered_map<Entity, size_t> entity_to_index_map;
    std::unordered_map<size_t, Entity> indexToEntityMap;
    size_t mSize;
};

#endif
