#include "charm.h"

int main()
{
    charm::AppOptions options;
    options.window_title = "Charmed Demo";

    charm::Application::create(options);
    return charmApp->exec();
}