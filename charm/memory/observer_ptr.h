#pragma once

#include <iostream>

namespace charm {

template <typename T>
class observer_ptr {
    T* m_ptr = nullptr;

public:
    observer_ptr(T* ptr)
        : m_ptr(ptr)
    {
    }

    ~observer_ptr()
    {
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
    observer_ptr(const observer_ptr<U>& other)
    {
        m_ptr = other.get();
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
    observer_ptr& operator=(const observer_ptr<U>& other)
    {
        if (this == &other)
            return *this;
        m_ptr = other.get();
        return *this;
    }

    T* operator->() const noexcept
    {
        return m_ptr;
    }

    T* get() const noexcept
    {
        return m_ptr;
    }

    bool operator==(const observer_ptr& other)
    {
        return m_ptr == other.m_ptr;
    }
};

}