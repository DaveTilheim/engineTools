#ifndef __EVENT_HANDLER_HPP__
#define __EVENT_HANDLER_HPP__

#include <SFML/Graphics.hpp>

class EventHandler
{
protected:
	virtual void closedEventHandler(sf::Event& event);
	virtual void keyPressedEventHandler(sf::Event& event);
	virtual void keyReleasedEventHandler(sf::Event& event);
	virtual void resizedEventHandler(sf::Event& event);
	virtual void lostFocusEventHandler(sf::Event& event);
	virtual void gainedFocusEventHandler(sf::Event& event);
	virtual void textEnteredEventHandler(sf::Event& event);
	virtual void mouseWheelMovedEventHandler(sf::Event& event);
	virtual void mouseWheelScrolledEventHandler(sf::Event& event);
	virtual void mouseButtonPressedEventHandler(sf::Event& event);
	virtual void mouseButtonReleasedEventHandler(sf::Event& event);
	virtual void mouseMovedEventHandler(sf::Event& event);
	virtual void mouseEnteredEventHandler(sf::Event& event);
	virtual void mouseLeftEventHandler(sf::Event& event);
	virtual void joystickButtonReleasedEventHandler(sf::Event& event);
	virtual void joystickButtonPressedEventHandler(sf::Event& event);
	virtual void joystickMovedEventHandler(sf::Event& event);
	virtual void joystickConnectedEventHandler(sf::Event& event);
	virtual void joystickDisconnectedEventHandler(sf::Event& event);
	virtual void touchBeganEventHandler(sf::Event& event);
	virtual void touchEndedEventHandler(sf::Event& event);
	virtual void touchMovedEventHandler(sf::Event& event);
	virtual void sensorChangedEventHandler(sf::Event& event);
	virtual void countEventHandler(sf::Event& event);
	virtual void handleEvent(sf::Event& event) final;
};

#endif
