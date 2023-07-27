#include <iostream>

#include "Core/Core.h"

#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

#include "SpaceGame.h"

#include <thread>

using namespace std;
using namespace kiko;

int main(int argc, char* argv[]) {

    MemoryTracker::Initialize();

    /////Setup

    seedRandom((unsigned int)time(nullptr));
    setFilePath("assets");
    cout << getFilePath() << endl;

    g_renderer.Initialize();
    g_renderer.CreateWindow("CSC195", 800, 600);

    g_inputSystem.Initialize();
    g_audioSystem.Initialize();

    unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
    game->Initialize();

    bool quit = false;
    while (!quit) {

        ///// Updates

        g_time.Tick();

        g_audioSystem.Update();
        g_inputSystem.Update();
        
        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

        game->Update(g_time.GetDeltaTime());

        /////// Drawing

        g_renderer.SetColor(0, 0, 0, 0);
        g_renderer.BeginFrame();

        game->Draw(g_renderer);

        g_renderer.EndFrame();

    }

    return 0;
}