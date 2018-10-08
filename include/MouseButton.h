#include <SFML/Graphics.hpp>

class MouseButton {
	sf::Mouse::Button button;

	bool pressed;
public:
	MouseButton(sf::Mouse::Button);

	bool getButton();
	bool getButtonDown();
};