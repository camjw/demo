#ifndef DEMO_ECS_ENTITY_MANAGER_HPP
#define DEMO_ECS_ENTITY_MANAGER_HPP

#include <demo/ecs/ecs.hpp>

#include <queue>
#include <array>

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

        Entity CreateEntity()
	    {
		    assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
    
		    Entity id = availableEntities.front();
		    availableEntities.pop();
		    ++livingEntityCount;
    
		    return id;
	    }
    
	    void DestroyEntity(Entity entity)
	    {
		    assert(entity < MAX_ENTITIES && "Entity out of range.");
    
		    signatures[entity].reset();
    
		    availableEntities.push(entity);
		    --livingEntityCount;
	    }
    
	    void SetSignature(Entity entity, Signature signature)
	    {
		    assert(entity < MAX_ENTITIES && "Entity out of range.");
    
		    signatures[entity] = signature;
	    }
    
	    Signature GetSignature(Entity entity)
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
