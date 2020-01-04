#ifndef INPUTENTITY_HPP
#define INPUTENTITY_HPP
#include "TextEntity.hpp"


enum Side
{
	LEFT,
	CENTER,
	RIGHT
};

class InputEntity : public TextEntity
{
private:
	bool focused = false;
	bool allowNewLine = false;
protected:
	static const int DELETE_CHAR;
	static const int NEW_LINE_CHAR;
public:
	using TextEntity::TextEntity;
	virtual ~InputEntity();
	InputEntity& operator=(const InputEntity& cp);
	void setFocus(bool f);
	void setNewLine(bool nl);
	void side(Side side); // to terminate
	bool isFocused() const;
	void input(const sf::Event::TextEvent& event);
	friend ostream &operator<<(ostream& out, const InputEntity& obj);

};

#endif
