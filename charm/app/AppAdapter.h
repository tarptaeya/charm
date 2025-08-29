#pragma once

#include "ui/Document.h"

namespace charm {

class AppAdapter {
public:
    AppAdapter(ui::Document& document)
        : m_document(document)
    {
    }

    virtual ~AppAdapter() { }
    virtual void update(double delta_time) = 0;

protected:
    ui::Document& m_document;
};

}