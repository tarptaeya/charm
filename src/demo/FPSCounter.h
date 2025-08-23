#pragma once

#include <deque>

class FPSCounter {
    const int MAX_SIZE = 500;
    std::deque<double> m_values;
    FPSCounter() = default;

public:
    void push(double value)
    {
        m_values.push_back(value);
        if (m_values.size() > MAX_SIZE)
            m_values.pop_front();
    }

    double get() const
    {
        double total = 0;
        for (double x : m_values)
            total += x;
        return m_values.size() / total;
    }

    static FPSCounter& get_instance()
    {
        static FPSCounter counter;
        return counter;
    }
};