#pragma once

#include "IElement.h"
#include <vector>

namespace charm {

class Panel : public IElement {
    std::vector<IElement*> m_children;

public:
    Panel();
    ~Panel();

    Panel(const Panel&) = delete;
    Panel& operator=(const Panel&) = delete;

    Panel(Panel&&) noexcept;
    Panel& operator=(Panel&&) noexcept;

    template <typename T, typename... Args>
    void add(Args&&... args)
    {
        T* element = new T(std::forward<Args>(args)...);
        m_children.push_back(element);
    }

    void update(double delta_time) override;
    void render() override;
};

}