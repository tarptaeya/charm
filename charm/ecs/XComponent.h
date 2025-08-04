#pragma once

class XEntity;

class XComponent {
    XEntity& m_entity;

public:
    explicit XComponent(XEntity&);
    virtual ~XComponent() = default;

    XComponent(const XComponent&) = delete;
    XComponent& operator=(const XComponent&) = delete;
};
