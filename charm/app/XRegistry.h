#pragma once

#include <string>
#include <unordered_map>

template <typename T>
class XRegistry {
    friend class XApplication;

    std::unordered_map<std::string, T> m_items;
    explicit XRegistry() = default;

public:
    ~XRegistry() = default;

    XRegistry(const XRegistry&) = delete;
    XRegistry& operator=(const XRegistry&) = delete;

    void add(const std::string& id, T&& item)
    {
        m_items[id] = std::move(item);
    }

    T& get(const std::string& id)
    {
        return m_items.at(id);
    }
};