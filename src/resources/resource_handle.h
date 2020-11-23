#ifndef DEMO_RESOURCE_HANDLE_H
#define DEMO_RESOURCE_HANDLE_H

#include <typeindex>

using ResourceID = uint32_t;

struct ResourceHandle
{
    ResourceHandle()
        : type(typeid(void))
        , instance_index(0)
    {
    }

    ResourceHandle(std::type_index type, ResourceID instance_index)
        : type(type)
        , instance_index(instance_index)
    {
    }

    std::type_index type;
    ResourceID instance_index;

    static bool is_valid(ResourceHandle r)
    {
        return r.instance_index > 0;
    }

    template <typename T>
    static ResourceHandle invalid_handle()
    {
        return ResourceHandle(std::type_index(typeid(T)), 0);
    }

    bool operator==(const ResourceHandle& other)
    {
        return type == other.type && instance_index == other.instance_index;
    }

    bool operator!=(const ResourceHandle& other)
    {
        return !(operator==(other));
    }

    bool operator<(const ResourceHandle& other)
    {
        if (type < other.type)
        {
            return true;
        }

        if (other.type < type)
        {
            return false;
        }

        return instance_index < other.instance_index;
    }

    bool operator>(const ResourceHandle& other)
    {
        return !(operator<(other));
    }

    bool operator<=(const ResourceHandle& other)
    {
        return operator==(other) || operator<(other);
    }

    bool operator>=(const ResourceHandle& other)
    {
        return operator==(other) || operator>(other);
    }
};

inline bool operator==(const ResourceHandle& lhs, const ResourceHandle& rhs)
{
    return lhs.type == rhs.type && lhs.instance_index == rhs.instance_index;
}

inline bool operator!=(const ResourceHandle& lhs, const ResourceHandle& rhs)
{
    return !(lhs == rhs);
}

inline bool operator<(const ResourceHandle& lhs, const ResourceHandle& rhs)
{
    if (lhs.type < rhs.type)
    {
        return true;
    }

    if (rhs.type < lhs.type)
    {
        return false;
    }

    return lhs.instance_index < rhs.instance_index;
}

inline bool operator>(const ResourceHandle& lhs, const ResourceHandle& rhs)
{
    return !(lhs == rhs || lhs < rhs);
}

inline bool operator<=(const ResourceHandle& lhs, const ResourceHandle& rhs)
{
    return lhs == rhs || lhs < rhs;
}

inline bool operator>=(const ResourceHandle& lhs, const ResourceHandle& rhs)
{
    return lhs == rhs || lhs > rhs;
}

namespace std
{
    template <>
    struct hash<ResourceHandle>
    {
        size_t operator()(const ResourceHandle& resource_handle) const
        {
            return hash<uint32_t>()(resource_handle.instance_index) + 17 * hash<std::type_index>()(resource_handle.type);
        }
    };
}

#endif // DEMO_RESOURCE_HANDLE_H
