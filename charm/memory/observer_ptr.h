#pragma once

namespace charm {

template <typename T>
class observer_ptr {
    T* m_ptr;

public:
    observer_ptr(T* ptr)
        : m_ptr(ptr)
    {
    }

    ~observer_ptr()
    {
    }

    observer_ptr(const observer_ptr& other)
    {
        m_ptr = other.m_ptr;
    }

    observer_ptr& operator=(const observer_ptr& other)
    {
        if (this == &other)
            return *this;
        m_ptr = other.m_ptr;
        return *this;
    }

    observer_ptr(observer_ptr&& other)
    {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    observer_ptr& operator=(observer_ptr&& other)
    {
        if (this == &other)
            return *this;

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;

        return *this;
    }

    T* operator->()
    {
        return m_ptr;
    }
};

}