#ifndef DEMO_RESOURCE_MANAGER_HPP
#define DEMO_RESOURCE_MANAGER_HPP

#include "resource_handle.h"
#include "resource_factory.h"
#include <map>
#include <typeindex>

class ResourceManager
{
public:
    template<typename T>
    bool add_factory(ResourceFactory<T>* factory)
    {
        std::type_index factory_type_index = std::type_index(typeid(T));
        auto existing_factory = resource_factories.find(factory_type_index);

        if (existing_factory != resource_factories.end())
        {
            return false;
        }

        IResourceFactory* abstract_factory = static_cast<IResourceFactory*>(factory);
        resource_factories[std::type_index(typeid(T))] = abstract_factory;
        return true;
    }

    std::map<std::type_index, IResourceFactory*> resource_factories;

    template <class T>
    ResourceHandle load(const std::string& name)
    {
        std::type_index type_index = std::type_index(typeid(T));
        auto factory = resource_factories.find(type_index);
        if (factory == resource_factories.end())
        {
            return ResourceHandle::invalid_handle<T>();
        }

        return factory->second->load(name);
    }

    template <class T>
    ResourceHandle insert(const std::string& name, T&& resource)
    {
        std::type_index type_index = std::type_index(typeid(T));
        auto factory = resource_factories.find(type_index);
        if (factory == resource_factories.end())
        {
            return ResourceHandle::invalid_handle<T>();
        }

        ResourceFactory<T>* resource_factory = static_cast<ResourceFactory<T>*>(factory->second);

        return resource_factory->insert(name, std::move(resource));
    }

    template <class T>
    T* get (const std::string& name)
    {
        std::type_index type_index = std::type_index(typeid(T));
        auto factory = resource_factories.find(type_index);
        if (factory == resource_factories.end())
        {
            return nullptr;
        }

        ResourceFactory<T>* resource_factory = static_cast<ResourceFactory<T>*>(factory->second);
        return resource_factory->get(name);
    }

    template <class T>
    T* get (const ResourceHandle& id) const
    {
        std::type_index type_index = id.type;
        auto factory = resource_factories.find(type_index);
        if (factory == resource_factories.end())
        {
            return nullptr;
        }

        ResourceFactory<T>* resource_factory = static_cast<ResourceFactory<T>*>(factory->second);
        return resource_factory->get(id);
    }

    template <class T>
    void for_each(std::function<void(T*)> callback) const
    {
        std::type_index type_index = std::type_index(typeid(T));
        auto abstract_factory = resource_factories.find(type_index);
        assert(abstract_factory != resource_factories.end() && "No matching resource factory registered");

        ResourceFactory<T>* factory = static_cast<ResourceFactory<T>*>(abstract_factory->second);

        factory->for_each(callback);
    }
};

#endif // DEMO_RESOURCE_MANAGER_HPP