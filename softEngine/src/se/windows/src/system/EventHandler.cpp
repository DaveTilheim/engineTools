#include <system/EventHandler.hpp>


void EventHandler::keyPressedEventHandler(const sf::Event& event)
{

}

void EventHandler::keyReleasedEventHandler(const sf::Event& event)
{

}

void EventHandler::resizedEventHandler(const sf::Event& event)
{

}

void EventHandler::lostFocusEventHandler(const sf::Event& event)
{

}

void EventHandler::gainedFocusEventHandler(const sf::Event& event)
{

}

void EventHandler::textEnteredEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseWheelMovedEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseWheelScrolledEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseButtonPressedEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseButtonReleasedEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseMovedEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseEnteredEventHandler(const sf::Event& event)
{

}

void EventHandler::mouseLeftEventHandler(const sf::Event& event)
{

}

void EventHandler::joystickButtonReleasedEventHandler(const sf::Event& event)
{

}

void EventHandler::joystickButtonPressedEventHandler(const sf::Event& event)
{

}

void EventHandler::joystickMovedEventHandler(const sf::Event& event)
{

}

void EventHandler::joystickConnectedEventHandler(const sf::Event& event)
{

}

void EventHandler::joystickDisconnectedEventHandler(const sf::Event& event)
{

}

void EventHandler::touchBeganEventHandler(const sf::Event& event)
{

}

void EventHandler::touchEndedEventHandler(const sf::Event& event)
{

}

void EventHandler::touchMovedEventHandler(const sf::Event& event)
{

}

void EventHandler::sensorChangedEventHandler(const sf::Event& event)
{

}

void EventHandler::countEventHandler(const sf::Event& event)
{

}

void EventHandler::closedEventHandler(const sf::Event& event)
{
	
}

void EventHandler::handleEvent(const sf::Event& event)
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
