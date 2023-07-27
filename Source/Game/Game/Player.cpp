#include "Player.h"
#include "Projectile.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include <memory>

void Player::Update(float dt) {

    Actor::Update(dt);

    bool sprint = kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT);

    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
    m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

    float thrust = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
    AddForce(forward * m_speed * thrust * ((sprint) ? 2.0f : 1.0f));
    
    m_transform.position.x = kiko::Wrap(m_transform.position.x, kiko::g_renderer.GetWidth());
    m_transform.position.y = kiko::Wrap(m_transform.position.y, kiko::g_renderer.GetHeight());



    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(
            400.0f, 
            kiko::Transform{m_transform.position, m_transform.rotation, 1}, 
            m_model, 
            GetTag(),
            10.0f, 
            2.0f,
            0.0f
            );

        m_scene->Add(std::move(projectile));
    
    }

}

void Player::OnCollision(Actor* other)
{
}
