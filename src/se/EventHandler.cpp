#include "EventHandler.hpp"


void EventHandler::keyPressedEventHandler(sf::Event& event)
{

}

void EventHandler::keyReleasedEventHandler(sf::Event& event)
{

}

void EventHandler::resizedEventHandler(sf::Event& event)
{

}

void EventHandler::lostFocusEventHandler(sf::Event& event)
{

}

void EventHandler::gainedFocusEventHandler(sf::Event& event)
{

}

void EventHandler::textEnteredEventHandler(sf::Event& event)
{

}

void EventHandler::mouseWheelMovedEventHandler(sf::Event& event)
{

}

void EventHandler::mouseWheelScrolledEventHandler(sf::Event& event)
{

}

void EventHandler::mouseButtonPressedEventHandler(sf::Event& event)
{

}

void EventHandler::mouseButtonReleasedEventHandler(sf::Event& event)
{

}

void EventHandler::mouseMovedEventHandler(sf::Event& event)
{

}

void EventHandler::mouseEnteredEventHandler(sf::Event& event)
{

}

void EventHandler::mouseLeftEventHandler(sf::Event& event)
{

}

void EventHandler::joystickButtonReleasedEventHandler(sf::Event& event)
{

}

void EventHandler::joystickButtonPressedEventHandler(sf::Event& event)
{

}

void EventHandler::joystickMovedEventHandler(sf::Event& event)
{

}

void EventHandler::joystickConnectedEventHandler(sf::Event& event)
{

}

void EventHandler::joystickDisconnectedEventHandler(sf::Event& event)
{

}

void EventHandler::touchBeganEventHandler(sf::Event& event)
{

}

void EventHandler::touchEndedEventHandler(sf::Event& event)
{

}

void EventHandler::touchMovedEventHandler(sf::Event& event)
{

}

void EventHandler::sensorChangedEventHandler(sf::Event& event)
{

}

void EventHandler::countEventHandler(sf::Event& event)
{

}

void EventHandler::closedEventHandler(sf::Event& event)
{
	
}

void EventHandler::handleEvent(sf::Event& event)
{
	switch(event.type)
	{
		case sf::Event::Closed:
			closedEventHandler(event);
			break;

		case sf::Event::KeyPressed:
			keyPressedEventHandler(event);
			break;

		case sf::Event::KeyReleased:
			keyReleasedEventHandler(event);
			break;

		case sf::Event::Resized:
			resizedEventHandler(event);
			break;

		case sf::Event::LostFocus:
			lostFocusEventHandler(event);
			break;

		case sf::Event::GainedFocus:
			gainedFocusEventHandler(event);
			break;

		case sf::Event::TextEntered:
			textEnteredEventHandler(event);
			break;

		case sf::Event::MouseWheelMoved:
			mouseWheelMovedEventHandler(event);
			break;

		case sf::Event:: MouseWheelScrolled:
			mouseWheelScrolledEventHandler(event);
			break;

		case sf::Event::MouseButtonPressed:
			mouseButtonPressedEventHandler(event);
			break;

		case sf::Event::MouseButtonReleased:
			mouseButtonReleasedEventHandler(event);
			break;

		case sf::Event::MouseMoved:
			mouseMovedEventHandler(event);
			break;

		case sf::Event::MouseEntered:
			mouseEnteredEventHandler(event);
			break;

		case sf::Event::MouseLeft:
			mouseLeftEventHandler(event);
			break;

		case sf::Event::JoystickButtonReleased:
			joystickButtonReleasedEventHandler(event);
			break;

		case sf::Event::JoystickButtonPressed:
			joystickButtonPressedEventHandler(event);
			break;

		case sf::Event::JoystickMoved:
			joystickMovedEventHandler(event);
			break;

		case sf::Event::JoystickConnected:
			joystickConnectedEventHandler(event);
			break;

		case sf::Event::JoystickDisconnected:
			joystickDisconnectedEventHandler(event);
			break;

		case sf::Event::TouchBegan:
			touchBeganEventHandler(event);
			break;

		case sf::Event::TouchEnded:
			touchEndedEventHandler(event);
			break;

		case sf::Event::TouchMoved:
			touchMovedEventHandler(event);
			break;

		case sf::Event::SensorChanged:
			sensorChangedEventHandler(event);
			break;

		case sf::Event::Count:
			countEventHandler(event);
			break;
	}
}
