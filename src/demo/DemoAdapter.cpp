#include "DemoAdapter.h"

using namespace charm;

DemoAdapter::DemoAdapter()
{
    charmShaders.add("basic", Shader(FileIO::read_text("assets/basic.vertex.glsl"), FileIO::read_text("assets/basic.fragment.glsl")));
    charmShaders.add("ui", Shader(FileIO::read_text("assets/ui.vertex.glsl"), FileIO::read_text("assets/ui.fragment.glsl")));
    charmShaders.add("screen", Shader(FileIO::read_text("assets/screen.vertex.glsl"), FileIO::read_text("assets/screen.fragment.glsl")));
    charmShaders.add("font-test", Shader(FileIO::read_text("assets/font-test.vertex.glsl"), FileIO::read_text("assets/font-test.fragment.glsl")));
    charmGeometries.add("box", Geometry::box());
}

DemoAdapter::~DemoAdapter()
{
}

void DemoAdapter::update(double delta_time)
{
}

void DemoAdapter::on_key_input(int key, int scancode, int action, int mods)
{
}

void DemoAdapter::on_mouse_button(int button, int action, int mods)
{
}