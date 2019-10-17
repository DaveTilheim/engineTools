#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <SFML/Graphics.hpp>

class EventHandler
{
protected:
	virtual void closedEventHandler(const sf::Event& event);
	virtual void keyPressedEventHandler(const sf::Event& event);
	virtual void keyReleasedEventHandler(const sf::Event& event);
	virtual void resizedEventHandler(const sf::Event& event);
	virtual void lostFocusEventHandler(const sf::Event& event);
	virtual void gainedFocusEventHandler(const sf::Event& event);
	virtual void textEnteredEventHandler(const sf::Event& event);
	virtual void mouseWheelMovedEventHandler(const sf::Event& event);
	virtual void mouseWheelScrolledEventHandler(const sf::Event& event);
	virtual void mouseButtonPressedEventHandler(const sf::Event& event);
	virtual void mouseButtonReleasedEventHandler(const sf::Event& event);
	virtual void mouseMovedEventHandler(const sf::Event& event);
	virtual void mouseEnteredEventHandler(const sf::Event& event);
	virtual void mouseLeftEventHandler(const sf::Event& event);
	virtual void joystickButtonReleasedEventHandler(const sf::Event& event);
	virtual void joystickButtonPressedEventHandler(const sf::Event& event);
	virtual void joystickMovedEventHandler(const sf::Event& event);
	virtual void joystickConnectedEventHandler(const sf::Event& event);
	virtual void joystickDisconnectedEventHandler(const sf::Event& event);
	virtual void touchBeganEventHandler(const sf::Event& event);
	virtual void touchEndedEventHandler(const sf::Event& event);
	virtual void touchMovedEventHandler(const sf::Event& event);
	virtual void sensorChangedEventHandler(const sf::Event& event);
	virtual void countEventHandler(const sf::Event& event);
	virtual void handleEvent(const sf::Event& event) final;
};

#endif
