#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Projectile : public kiko::Actor {

public:

	Projectile(float speed, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model, std::string tag, float damage, float lifespan, float damping) :
		Actor{ transform, model, tag, -1.0f, damping, lifespan },
		m_speed{ speed },
		m_damage{damage}
	{ 
		kiko::g_audioSystem.Play("laser");
	};

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:

	float m_speed = 0;
	float m_damage = 0;
};

