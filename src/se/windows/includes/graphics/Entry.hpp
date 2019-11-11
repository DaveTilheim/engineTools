#ifndef ENTRY_HPP
#define ENTRY_HPP
#include "Label.hpp"
#include "KeyCatcher.hpp"

namespace se
{
	class Entry : public Label, public KeyCatcher
	{
	protected:
		bool allowNewline = true;
		std::string newlineStr = "";
		bool sizeLocked = false;
		bool cursorKeysRelease = true;
		void outOfBounds();
		bool focus=false;
		sf::Color focusedColor = sf::Color::White;
		sf::Color unfocusedColor = sf::Color::Black;
		unsigned cursor = 0;
		void insert(std::string, int pos=-1);
		void insert(char, int pos=-1);
		void removeAt(int pos=-1);
	public:
		Entry(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color=sf::Color::White);
		virtual void update() override;
		virtual void keyCatch(char keycode) override;
		void allowNewLine(bool b=true);
		void setNewlineStr(std::string nlstr="");
		void lockSize(bool lock=true);
		void setFocusedColor(const sf::Color&);
		void setUnfocusedColor(const sf::Color&);
	};
}

#endif
