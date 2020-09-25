#ifndef DEMO_UNORDERED_MAP_H
#define DEMO_UNORDERED_MAP_H

namespace dtl
{

template <class K, class V>
class unordered_map_node
{
public:
    unordered_map_node(K key, V value)
        : _key(key)
        , _value(value)
        , next(nullptr)
        , prev(nullptr)
    {
    }

    inline const K& key() const
    {
        return _key;
    }

    inline V& value() const
    {
        return _value;
    }

    inline void insert_after(unordered_map_node<K, V>* to_insert)
    {
        to_insert->prev = this;
        next = to_insert;
    }

private:
    K _key;
    V _value;
    unordered_map_node* next;
    unordered_map_node* prev;
};

template <class K>
struct simple_hasher
{
    unsigned long operator()(K key)
    {
        return static_cast<unsigned long>(&key);
    }
};

template <class K, class V, class F = simple_hasher<K>>
class unordered_map
{
public:
    unordered_map()
        : num_buckets(DEFAULT_NUM_BUCKETS)
    {
        buckets = new unordered_map_node<K, V>*[num_buckets]();
    };

    unordered_map(int num_buckets)
        : num_buckets(num_buckets)
    {
        buckets = new unordered_map_node<K, V>*[num_buckets]();
    };

    ~unordered_map()
    {
        for (int i = 0; i < num_buckets; i++)
        {
            unordered_map_node<K, V>* current = buckets[i];
            unordered_map_node<K, V>* next;
            while(current != nullptr)
            {
                next = current->next;
                delete current;
                current = next;
            }
        }

        delete buckets;
    }

    inline void insert(K key, V value)
    {
        int bucket_index = F(key) % num_buckets;
        if (buckets[bucket_index] == nullptr)
        {
            buckets[bucket_index] = new unordered_map_node<K, V>(key, value);
        }
        else
        {
            buckets[bucket_index]->insert_after(new unordered_map_node<K, V>(key, value));
        }
    }

    inline bool contains(const K& key)
    {
        unordered_map_node<K, V>* current = buckets[F(key) % num_buckets];

        while (current != nullptr)
        {
            if (current->key() == key)
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    V& operator[](const K& key)
    {
        if (!contains(key))
        {
            V new_value = V();
            insert(key, V());
            return new_value;
        }

        return find(key)->value();
    }

    const V& operator[](const K& key) const
    {
        if (!contains(key))
        {
            V new_value = V();
            insert(key, V());
            return new_value;
        }

        return find(key)->value();
    }

    bool try_get(const K& key, V* output) const
    {
        unordered_map_node<K, V>* current = buckets[F(key) % num_buckets];

        while (current != nullptr)
        {
            if (current->key() == key)
            {
                *output = current->value();
                return true;
            }

            current = current->next;
        }

        return false;
    }

    inline bool remove(const K& key)
    {
        unordered_map_node<K, V>* current = buckets[F(key) % num_buckets];
        while (current != nullptr)
        {
            if (current->key() == key)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }

                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }

                delete current;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    bool remove(const K& key, V* output)
    {
        unordered_map_node<K, V>* current = buckets[F(key) % num_buckets];
        while (current != nullptr)
        {
            if (current->key() == key)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }

                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }

                *output = current->value();
                delete current;
                return true;
            }

            current = current->next;
        }

        return false;
    }



private:
    int num_buckets;
    unordered_map_node<K, V>* buckets[];
    static const int DEFAULT_NUM_BUCKETS = 100;
};

}
#endif // DEMO_UNORDERED_MAP_H
