#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace charm {

template <typename T>
class Registry {
    friend class Application;

    std::unordered_map<std::string, T> m_items;
    explicit Registry() = default;

public:
    ~Registry() = default;

    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;

    void add(const std::string& id, T&& item)
    {
        if (m_items.count(id)) {
            std::cout << "[warn] overriding item with id = " << id << ", which is already present in registery" << std::endl;
        }

        m_items[id] = std::move(item);
    }

    T& get(const std::string& id)
    {
        return m_items.at(id);
    }
};

}