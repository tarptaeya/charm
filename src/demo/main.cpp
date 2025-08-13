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

    Application::create<GameLoop>(options);
    return charmApp->exec();
}