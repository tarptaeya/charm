#pragma once

#include "charm.h"

#include "game_objects/RootObject.h"

class DemoAdapter : public charm::AppAdapter {
    charm::Camera m_camera;
    charm::Framebuffer m_main_framebuffer;
    charm::Framebuffer m_hud_framebuffer;

    RootObject m_root_object;
    charm::ui::Document m_document;

public:
    DemoAdapter();
    ~DemoAdapter() override;

    void update(double delta_time) override;

private:
    void update_hud_framebuffer(double delta_time);
    void update_screen_framebuffer(double delta_time);
    void update_main_framebuffer(double delta_time);

    void blit_framebuffer_to_screen(unsigned int texture_handle);
};