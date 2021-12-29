#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include "sfh_math.hpp"

namespace sfh {
	namespace shape {
		std::vector<sf::Vertex> line(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& col = sf::Color::White) {
			std::vector<sf::Vertex> vertArray(2);
			vertArray[0].position = p1;
			vertArray[0].color = col;
			vertArray[1].position = p2;
			vertArray[1].color = col;
			return vertArray;
		}

		std::vector<sf::Vertex> thickLine(const sf::Vector2f& p1, const sf::Vector2f& p2,
			float size, const sf::Color& col = sf::Color::White) {
			std::vector<sf::Vertex> vertArray(4);
			sf::Vector2f unit_normal = sfh::normalize2d(sfh::normal({ p2.x - p1.x, p2.y - p1.y }).first);
			sf::Vector2f resized_normal = { unit_normal.x * size / 2.0f,  unit_normal.y * size / 2.0f };
			vertArray[0].position = { p1.x + resized_normal.x, p1.y + resized_normal.y };
			vertArray[0].color = col;
			vertArray[1].position = { p1.x - resized_normal.x, p1.y - resized_normal.y };
			vertArray[1].color = col;
			vertArray[2].position = { p2.x - resized_normal.x, p2.y - resized_normal.y };
			vertArray[2].color = col;
			vertArray[3].position = { p2.x + resized_normal.x, p2.y + resized_normal.y };
			vertArray[3].color = col;
			return vertArray;
		}

		std::vector<sf::Vertex> square(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& col = sf::Color::White) {
			std::vector<sf::Vertex> vertArray(4);
			vertArray[0].position = pos;
			vertArray[0].color = col;
			vertArray[1].position = { pos.x + size.x, pos.y };
			vertArray[1].color = col;
			vertArray[2].position = { pos.x + size.x, pos.y + size.y };
			vertArray[2].color = col;
			vertArray[3].position = { pos.x, pos.y + size.y };
			vertArray[3].color = col;
			return vertArray;
		}

		std::vector<sf::Vertex> triangle(const sf::Vector2f& pos, const sf::Vector2f& baseHight, const sf::Color& col = sf::Color::White) {
			std::vector<sf::Vertex> vertArray(3);
			vertArray[0].position = pos;
			vertArray[0].color = col;
			vertArray[1].position = { pos.x - baseHight.x / 2.0f, pos.y + baseHight.y };
			vertArray[1].color = col;
			vertArray[2].position = { pos.x + baseHight.x / 2.0f, pos.y + baseHight.y };
			vertArray[2].color = col;
			return vertArray;
		}

	}
}