#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "sfh_color.hpp"

class App {
public:
	App() = default;
	App(App& app) = delete;
	App operator=(App& app) = delete;
	~App() = default;

	virtual void create_window() {
		settings.antialiasingLevel = 8;
		vid = sf::VideoMode::getDesktopMode();

		window.create(vid, name, sf::Style::Fullscreen, settings);

		width = vid.width;
		height = vid.height;

		window.setVerticalSyncEnabled(true);
	}

	virtual void run() {
		setup();
		while (window.isOpen()) {
			frameTime = clock.getElapsedTime().asSeconds();
			clock.restart();
			frameRate = std::round(1.0f / frameTime);
			while (window.pollEvent(event)) {
				eventManager();
			}
			loop();
		}
	}

	virtual void setup() = 0;
	virtual void loop() = 0;

	virtual void Close() {
		window.close();
	}

	virtual void KeyPressedEvent() {}
	virtual void KeyReleasedEvent() {}
	virtual void MouseButtonPressedEvent() {}
	virtual void MouseButtonReleasedEvent() {}
	virtual void ClosedEvent() {
		Close();
	}
	virtual void LostFocusEvent() {}
	virtual void GainedFocusEvent() {}
	virtual void MouseEnteredEvent() {}
	virtual void MouseLeftEvent() {}
	virtual void MouseMovedEvent() {}
	virtual void MouseWheelScrolledEvent() {}
	virtual void TextEnteredEvent() {}

	virtual void eventManager() {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			KeyPressedEvent();
			break;
		case sf::Event::KeyReleased:
			KeyReleasedEvent();
			break;
		case sf::Event::MouseButtonPressed:
			MouseButtonPressedEvent();
			break;
		case sf::Event::MouseButtonReleased:
			MouseButtonReleasedEvent();
			break;
		case sf::Event::Closed:
			ClosedEvent();
			break;
		case sf::Event::LostFocus:
			LostFocusEvent();
			break;
		case sf::Event::GainedFocus:
			GainedFocusEvent();
			break;
		case sf::Event::MouseEntered:
			MouseEnteredEvent();
			break;
		case sf::Event::MouseLeft:
			MouseLeftEvent();
			break;
		case sf::Event::MouseMoved:
			MouseMovedEvent();
			break;
		case sf::Event::MouseWheelScrolled:
			MouseWheelScrolledEvent();
			break;
		case sf::Event::TextEntered:
			TextEnteredEvent();
			break;
		default:
			break;
		}
	}
protected:
	sf::RenderWindow window;
	sf::VideoMode vid;
	sf::ContextSettings settings;
	std::string name;
	sf::Event event = sf::Event();
	sf::Clock clock;
	int width = 0, height = 0;
	float frameTime;
	int frameRate;
};