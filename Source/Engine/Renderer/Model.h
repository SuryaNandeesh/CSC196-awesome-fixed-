#pragma once

#include "Core/Core.h"
#include "Renderer.h"
#include <vector>

namespace kiko {

	class Model {


	public:

		Model() = default;
		Model(std::vector<vec2> points) : m_points{ points } {}
		Model(const std::string& filename) { Load(filename); }

		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();

	private:

		std::vector<vec2> m_points;
		float m_radius;
		Color m_color;

	};

}