#include "SpaceGame.h"

#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"

#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"


using namespace kiko;

bool SpaceGame::Initialize() {

    m_font = std::make_shared<Font>("ARCADECLASSIC.ttf", 24);

	m_scoreText = std::make_unique<Text>(m_font);
    m_scoreText->Create(kiko::g_renderer, "Score: ", kiko::Color{ 1, 1, 1, 1 });

	m_livesText = std::make_unique<Text>(m_font);
    m_livesText->Create(kiko::g_renderer, "Lives: ", kiko::Color{ 1, 1, 1, 1 });

    m_titleText = std::make_unique<Text>(m_font);
    m_titleText->Create(kiko::g_renderer, "ASTEROID", kiko::Color{ 1, 1, 1, 1 });

	g_audioSystem.AddAudio("laser", "laser.wav");

    m_scene = std::make_unique<Scene>();

	return true;

}



void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt) {

	switch (m_state) {

	case SpaceGame::Title:

       if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
            m_state = eState::StateGame;

		break;

	case SpaceGame::StateGame:

        m_score = 0;
        m_lives = 0;
        m_state = eState::StartLevel;

		break;

	case SpaceGame::StartLevel:

        m_scene->Add(std::make_unique<Player>(
            100.0f,
            10.0f,
            DegToRad(270.0f),
            Transform{ {400, 300}, 0, 3 },
            g_manager.Get("ship.txt"), 
            "Player",
            0.95f
            ));

        m_state = eState::Game;

		break;

	case SpaceGame::Game:

        m_spawnTimer += dt;

        if (m_spawnTimer >= m_spawnTime) {

            m_spawnTimer = 0;

            m_scene->Add(std::make_unique <Enemy>(
                20.0f,
                randomf(10.0f, 20.0f),
                DegToRad(270.0f),
                Transform{
                    {randomf((float) g_renderer.GetWidth()), (float) randomf(g_renderer.GetHeight()) },
                    randomf(kiko::TwoPi),
                    2
                },
                g_manager.Get("enemy.txt"),
                randomf(1, 2),
                "Enemy",
                .95f
                ));

        }

		break;

	case SpaceGame::PlayerDead:
		break;

	case SpaceGame::GameOver:
		break;

	default:
		break;

	}

    m_scoreText->Create(g_renderer, "Score " + std::to_string(m_score), { 1, 1, 1, 1 });

    m_scene->Update(dt);
    g_particleSystem.Update(dt);

}

void SpaceGame::Draw(kiko::Renderer& renderer) {
    
    if (m_state == eState::Title)
        m_titleText->Draw(g_renderer, 400, 300);
    
    m_scene->Draw(renderer);
    g_particleSystem.Draw(renderer);
    
}
