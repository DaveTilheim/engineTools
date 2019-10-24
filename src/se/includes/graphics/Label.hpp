#ifndef LABEL_HPP
#define LABEL_HPP
#include "Widget.hpp"
#include <sstream>

namespace se
{
	class Label : public Widget
	{
	protected:
		sf::Text *text = nullptr;
		unsigned padd = 0;
	public:
		Label(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color=sf::Color::White);
		virtual ~Label();
		sf::Text &getText();
		std::string getString();
		void setText(std::string text);
		void setTextWithoutChange(std::string text);
		void updatePadding();
		std::vector<std::string> getLines();
		std::string getLastLine();
		std::string getFirstLine();
		std::vector<std::string> getWords(unsigned lineid=0);
		std::vector<std::string> getWords(std::string);
		void setCharSize(unsigned s);
		virtual void render() override;
		virtual void setPosition(float x, float y) override;
		virtual void setTLPosition(float x, float y) override;
		virtual void setRotation(float angle) override;
		virtual void rotate(float angle) override;
		virtual void move(float x, float y) override;
		virtual void setOrigin(float x, float y) override;
		virtual void setSize(sf::Vector2f v) override;
		virtual void setSize(unsigned csize, unsigned padding=0);
		virtual void setScale(float sx, float sy) override;
		virtual void setScale(float s);
		virtual void padding(unsigned pdg);
		virtual void center();
		virtual void left();
		virtual void right();
		virtual void top();
		virtual void bottom();
		virtual void setTextFillColor(const sf::Color &c);
	};
}

#endif
