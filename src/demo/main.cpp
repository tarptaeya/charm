#include "GameLoop.h"
#include "charm.h"
#include <iostream>

using namespace charm;

int main()
{
    AppOptions options;
    options.window_width = 1024;
    options.window_height = 720;
    options.window_title = "Charmed Demo";

    charmApp.initialize(options);

    charmShaders.add("basic", Shader(FileIO::read_text("assets/basic.vertex.glsl"), FileIO::read_text("assets/basic.fragment.glsl")));
    charmShaders.add("ui", Shader(FileIO::read_text("assets/ui.vertex.glsl"), FileIO::read_text("assets/ui.fragment.glsl")));
    charmShaders.add("screen", Shader(FileIO::read_text("assets/screen.vertex.glsl"), FileIO::read_text("assets/screen.fragment.glsl")));
    charmShaders.add("font-test", Shader(FileIO::read_text("assets/font-test.vertex.glsl"), FileIO::read_text("assets/font-test.fragment.glsl")));
    charmGeometries.add("box", Geometry::box());

    return charmApp.exec<GameLoop>();
}