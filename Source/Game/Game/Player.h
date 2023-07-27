#pragma once
#include "Framework/Actor.h"

class Player : public kiko::Actor {

public:

	Player(float health, float speed, float turnRate, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model, std::string tag, float damping) :
		Actor{ transform, model, tag, health, damping },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	
	float m_speed = 0;
	float m_turnRate = 0;

};

