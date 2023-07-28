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

    //seeds random to make it constantly randomizing
    seedRandom((unsigned int)time(nullptr));
    //file location
    setFilePath("assets");
    cout << getFilePath() << endl;
    //creation of window
    g_renderer.Initialize();
    g_renderer.CreateWindow("CSC196", 800, 600);
    //creates input system
    g_inputSystem.Initialize();
    g_audioSystem.Initialize();
    //creates the game itself
    unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
    game->Initialize();

    bool quit = false;
    while (!quit) {

        ///// Updates

        g_time.Tick();
        //updates the audio and input every tick
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