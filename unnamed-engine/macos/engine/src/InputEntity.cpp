#include "InputEntity.hpp"

const int InputEntity::DELETE_CHAR = 8;
const int InputEntity::NEW_LINE_CHAR = 10;

InputEntity::~InputEntity()
{

}

InputEntity& InputEntity::operator=(const InputEntity& cp)
{
	TextEntity::operator=(cp);
	focused = cp.focused;
	return *this;
}

void InputEntity::setFocus(bool f)
{
	focused = f;
}

void InputEntity::setNewLine(bool nl)
{
	allowNewLine = nl;
}

bool InputEntity::isFocused() const
{
	return focused;
}

void InputEntity::input(const sf::Event::TextEvent& event)
{
	auto code = event.unicode;
	if(code == DELETE_CHAR)
	{
		auto s = getString();
		if(s.getSize())
		{
			s.erase(s.getSize()-1, 1);
			setString(s);
		}
	}
	else
	{
		if(code == NEW_LINE_CHAR and not allowNewLine)
		{
			setFocus(false);
		}
		else
		{
			setString(getString() + event.unicode);
		}
	}
	//cout << code << endl;
	updateSideOrigin();
}

void InputEntity::side(Side side)
{
	int f = 0;
	sf::String s = getString();
	switch(side)
	{
		case Side::LEFT:
			while((f = s.find("\n", f)) != sf::String::InvalidPos)
			{
				while(s[f+1] == ' ')
				{
					s.erase(f+1);
				}
				f++;
			}
			break;

		case Side::RIGHT:

			break;

		case Side::CENTER:
			
			break;
	}
	setString(s);
	updateSideOrigin();
}

ostream &operator<<(ostream& out, const InputEntity& obj)
{
	return out << *dynamic_cast<const TextEntity *>(&obj) << "  focused: " << obj.focused;
}
