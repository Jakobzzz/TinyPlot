#pragma once
#include "../utils/ResourceHolder.hpp"
#include "../utils/ResourceIdentifiers.hpp"
#include <array>

namespace tp
{
	class Application
	{
	public:
		Application();
		void run();

	private:
		void loadFonts();
		void processEvents();
		void render();

	private:
		sf::RenderWindow m_window;
		sf::RectangleShape m_rect;
		std::array<sf::Text, 16> m_numbers;
		std::array<sf::Vertex, 64> m_vertex;
		FontHolder m_fonts;
	};
}
