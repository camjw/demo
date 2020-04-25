#ifndef DEMO_ECS_COMPONENT_ARRAY_HPP
#define DEMO_ECS_COMPONENT_ARRAY_HPP

#include <demo/ecs/ecs.hpp>

#include <unordered_map>

class IComponentArray
{
    public:
        virtual ~IComponentArray();
        virtual void on_entity_destroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray: public IComponentArray
{
    public:
        	void insert_data(Entity entity, T component)
	    {
		    assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
    
		    // Put new entry at end and update the maps
		    size_t newIndex = mSize;
		    entityToIndexMap[entity] = newIndex;
		    indexToEntityMap[newIndex] = entity;
		    componentArray[newIndex] = component;
		    ++mSize;
	    }
    
	    void remove_data(Entity entity)
	    {
		    assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");
    
		    // Copy element at end into deleted element's place to maintain density
		    size_t indexOfRemovedEntity = entityToIndexMap[entity];
		    size_t indexOfLastElement = mSize - 1;
		    componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
    
		    // Update map to point to moved spot
		    Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
		    entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		    indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
    
		    entityToIndexMap.erase(entity);
		    indexToEntityMap.erase(indexOfLastElement);
    
		    --mSize;
	    }
    
	    T& get_data(Entity entity)
	    {
		    assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
    
		    // Return a reference to the entity's component
		    return componentArray[entityToIndexMap[entity]];
	    }
    
	    void on_entity_destroyed(Entity entity) override
	    {
		    if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		    {
			    remove_data(entity);
		    }
	    }
    
    private:
	    std::array<T, MAX_ENTITIES> componentArray;
	    std::unordered_map<Entity, size_t> entityToIndexMap;
	    std::unordered_map<size_t, Entity> indexToEntityMap;
	    size_t mSize;
};

#endif

