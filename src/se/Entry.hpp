#ifndef ENTRY_HPP
#define ENTRY_HPP
#include "Label.hpp"

namespace se
{
	class Entry : public Label
	{
	private:
		bool allowNewline = true;
		std::string newlineStr = "";
		bool sizeLocked = false;
		void outOfBounds();
		bool focus=false;
		sf::Color focusedColor = sf::Color::White;
		sf::Color unfocusedColor = sf::Color::Black;
	public:
		Entry(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color=sf::Color::White);
		virtual void update() override;
		void keyCodeCatch(const char kcode);
		void allowNewLine(bool b=true);
		void setNewlineStr(std::string nlstr="");
		void lockSize(bool lock=true);
		void setFocusedColor(const sf::Color&);
		void setUnfocusedColor(const sf::Color&);
	};
}

#endif
