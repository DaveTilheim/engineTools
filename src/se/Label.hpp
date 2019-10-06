#ifndef LABEL_HPP
#define LABEL_HPP
#include "Widget.hpp"

namespace se
{
	class Label : public Widget
	{
	private:
		sf::Text *text = nullptr;
	public:
		Label(float x, float y, std::string text, sf::Font *font, Application *root, sf::Color=sf::Color::White);
		virtual ~Label();
		sf::Text &getText();
		void setText(std::string text);
		virtual void render() override;
		virtual void setPosition(float x, float y) override;
		virtual void setRotation(float angle) override;
		virtual void rotate(float angle) override;
		virtual void move(float x, float y) override;
		virtual void setOrigin(float x, float y) override;
		virtual void setSize(sf::Vector2f v) override;
		virtual void setSize(unsigned csize, unsigned padding=0);
		virtual void setScale(float sx, float sy) override;
		virtual void setScale(float s);
		virtual void center();
		virtual void left();
		virtual void right();
		virtual void top();
		virtual void bottom();
		virtual void setTextFillColor(const sf::Color &c);
	};
}

#endif
