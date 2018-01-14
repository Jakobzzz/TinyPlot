#include "Application.hpp"
#include <SFML\Window\Event.hpp>

namespace tp
{
	Application::Application() : m_window(sf::VideoMode(800, 600), "TinyPlot", sf::Style::Close, sf::ContextSettings(0, 0, 8))
	{
		loadFonts();

		//Bounding rect of the graph
		m_rect.setOrigin(sf::Vector2f(250.f, 200.f));
		m_rect.setPosition(sf::Vector2f(400.f, 300.f));
		m_rect.setSize(sf::Vector2f(500.f, 400.f));
		m_rect.setFillColor(sf::Color::Transparent);
		m_rect.setOutlineThickness(2.f);
		m_rect.setOutlineColor(sf::Color::Black);

		//Test for spacing points
		sf::Vector2f top = m_rect.getTransform().transformPoint(m_rect.getPoint(0));
		sf::Vector2f bottom = m_rect.getTransform().transformPoint(m_rect.getPoint(3));
		sf::Vector2f right = m_rect.getTransform().transformPoint(m_rect.getPoint(2));

		float p = 50.f;
		for (unsigned i = 0; i < m_vertex.size(); i += 2, p += 50.f)
		{
			if (i < 18) //Bottom points
			{
				m_vertex[i] = sf::Vertex(sf::Vector2f(bottom.x + p, bottom.y), sf::Color::Black);
				m_vertex[i + 1] = sf::Vertex(sf::Vector2f(bottom.x + p, bottom.y - 5.f), sf::Color::Black);
			}
			else if (i >= 18 && i < 36) //Top points
			{
				if (i == 18)
					p = 50.f;

				m_vertex[i] = sf::Vertex(sf::Vector2f(top.x + p, top.y), sf::Color::Black);
				m_vertex[i + 1] = sf::Vertex(sf::Vector2f(top.x + p, top.y + 5.f), sf::Color::Black);
			}
			else if (i >= 36 && i < 50) //Left points
			{
				if (i == 36)
					p = 50.f;

				m_vertex[i] = sf::Vertex(sf::Vector2f(bottom.x, bottom.y - p), sf::Color::Black);
				m_vertex[i + 1] = sf::Vertex(sf::Vector2f(bottom.x + 5.f, bottom.y - p), sf::Color::Black);
			}
			else if (i >= 50 && i < 64) //Right points
			{
				if (i == 50)
					p = 50.f;

				m_vertex[i] = sf::Vertex(sf::Vector2f(right.x, right.y - p), sf::Color::Black);
				m_vertex[i + 1] = sf::Vertex(sf::Vector2f(right.x - 5.f, right.y - p), sf::Color::Black);
			}
		}

		//Text test
		unsigned j = 0;
		sf::Vector2f offset(0.f, 15.f);

		for (unsigned i = 0; i < m_numbers.size(); ++i, j += 2)
		{
			if (i == 9) { j = 36; offset = sf::Vector2f(-15.f, 0.f); }

			m_numbers[i].setFont(m_fonts.GetResource(Fonts::ID::Main));
			m_numbers[i].setCharacterSize(15);
			m_numbers[i].setString(std::to_string(i + 1));
			m_numbers[i].setPosition(sf::Vector2f(m_vertex[j].position.x + offset.x, m_vertex[j].position.y + offset.y));
			m_numbers[i].setFillColor(sf::Color::Black);

			//Adjust origin of the text based on the alignment
			if (i < 9)
			{
				sf::FloatRect textRect = m_numbers[i].getLocalBounds();
				m_numbers[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			}
			else
			{
				sf::FloatRect textRect = m_numbers[i].getLocalBounds();
				m_numbers[i].setOrigin(textRect.width - textRect.left, textRect.top + textRect.height / 2.0f);
			}
		}
	}

	void Application::run()
	{
		while (m_window.isOpen())
		{
			processEvents();
			render();	
		}
	}

	void Application::loadFonts()
	{
		m_fonts.LoadResource(Fonts::ID::Main, "src/res/fonts/arial.ttf");
	}

	void Application::processEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				m_window.close();
		}
	}

	void Application::render()
	{
		m_window.clear(sf::Color(224, 224, 224, 255));
		m_window.draw(m_rect);

		for (auto number : m_numbers)
			m_window.draw(number);

		m_window.draw(m_vertex.data(), m_vertex.size(), sf::Lines);
		m_window.display();
	}
}