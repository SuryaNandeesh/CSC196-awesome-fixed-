#pragma once
#include "MathUtils.h"
#include <cstdint>
#include <istream>
#include <string>

namespace kiko {

	class Color {

	public:

		float r, g, b, a;

	public:

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {}
		Color(float r, float g, float b, float a = 0) : r{ r }, g{ g }, b{ b }, a{ a } {}

		static uint8_t ToInt(float c) { return static_cast<uint8_t> (Clamp(c, 0.0f, 1.0f) * 255); }

	};

	inline std::istream& operator >> (std::istream& stream, Color& c) {

		std::string line;
		std::getline(stream, line);

		std::string str = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		c.r = std::stof(str);
		line = line.substr(line.find(",") + 1);

		str = line.substr(0, line.find(","));
		c.g = std::stof(str);

		str = line.substr(line.find(",") + 1, line.find("}"));
		c.b = std::stof(str);

		return stream;

	}

}