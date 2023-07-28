#pragma once
#include "Audio/AudioSystem.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace kiko {

	class Actor {

	public:

		Actor() = default;
		Actor(const kiko::Transform& transform, std::shared_ptr<Model>& model, std::string tag, float health, float damping, float lifespan = -1.0f) :
			m_transform{ transform },
			m_model{ model },
			m_tag{ tag },
			m_lifespan{ lifespan },
			m_health{ health },
			m_damping{ damping }
		{}

		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		virtual void OnCollision(Actor* other) {};

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		float GetHealth() { return m_health; }
		std::string GetTag() { return m_tag; }
		Transform GetTransform() { return m_transform; }

		void SetLifespan(float lifespan) { m_lifespan = lifespan; }

		void AddForce(vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		virtual void Damage(float damage) { m_health -= damage; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

	protected:

		bool m_destroyed = false;
		float m_lifespan = -1.0f;
		float m_health = -1.0f;

		vec2 m_velocity;
		float m_damping = 0;

		Transform m_transform;
		std::string m_tag;
		std::shared_ptr<Model> m_model;

	};

}