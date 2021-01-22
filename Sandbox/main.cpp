#include "EngineX.h"

int main(int argc, char** argv)
{
    auto* app = new EngineX::Application();
    app->Run();
    delete app;

    return 0;
}
