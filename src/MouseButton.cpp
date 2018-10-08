#ifndef MOUSE_BUTTON
#define MOUSE_BUTTON

#include "MouseButton.h"

MouseButton::MouseButton(sf::Mouse::Button mouseButton) {
	button = mouseButton;
}

bool MouseButton::getButton() {
	return sf::Mouse::isButtonPressed(button);
}

bool MouseButton::getButtonDown() {
	if (!pressed) {
		pressed = sf::Mouse::isButtonPressed(button);
		return sf::Mouse::isButtonPressed(button);
	}
	else {
		pressed = sf::Mouse::isButtonPressed(button);
		return false;
	}
}

#endif