#pragma once

#include <deque>

class FPSCounter {
    const int MAX_SIZE = 5;
    std::deque<double> m_values;
    FPSCounter() = default;
    double m_tick_acc = 0;

public:
    void push(double value)
    {
        m_tick_acc += value;
        if (m_tick_acc < 0.1)
            return;

        m_tick_acc = 0;

        m_values.push_back(value);
        if (m_values.size() > MAX_SIZE)
            m_values.pop_front();
    }

    double get() const
    {
        double total = 0;
        for (double x : m_values)
            total += x;
        return std::round(m_values.size() / total);
    }

    static FPSCounter& get_instance()
    {
        static FPSCounter counter;
        return counter;
    }
};