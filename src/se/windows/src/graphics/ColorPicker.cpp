#include <graphics/ColorPicker.hpp>

using namespace se;

ColorPicker::ColorPicker(float x, float y, float w, float h, Application *root, const sf::Color& color, sf::Font *font)
: LinkedEntity<Widget>(x, y, w, h, root),
PixelPicker(new sf::Texture(), 256, 256, this),
viewRect(0,0,20,root)
{
	setOutline(sf::Color::Black, 3);
	viewRect.setOutline(sf::Color(0,0,0,127), 2);
	auto p = getTLPosition();
	viewRect.setPosition(p.x, p.y);
	if(font)
	{
		onLeftHoldClick(
		[this](Widget *w)
		{
			auto m = util::getMousePosition();
			auto c = getCoordinates(m.x, m.y);
			auto p = getTLPosition();
			auto color = getColorAt(m);
			viewRect.setPosition(p.x + c.x *(1/ (256.0/getSize().x)), p.y + c.y * (1/(256.0/getSize().y)));
			viewRect.setFillColor(color);
			pickedValue = color;
			textColorValue->setTextWithoutChange(std::to_string(color.r)+" "+std::to_string(color.g)+" "+std::to_string(color.b)+" "+std::to_string(color.a));
			onChange = true;
		},
		[this](Widget *w)
		{
			onChange = false;
		});
	}
	else
	{
		onLeftHoldClick(
		[this](Widget *w)
		{
			auto m = util::getMousePosition();
			auto c = getCoordinates(m.x, m.y);
			auto p = getTLPosition();
			auto color = getColorAt(m);
			viewRect.setPosition(p.x + c.x *(1/ (256.0/getSize().x)), p.y + c.y * (1/(256.0/getSize().y)));
			viewRect.setFillColor(color);
			pickedValue = color;
			onChange = true;
		},
		[this](Widget *w)
		{
			onChange = false;
		});
	}
	addTexture("_basic_color_picker0x0", colorPickerTxtr);
	setTexture("_basic_color_picker0x0");
	setMainColor(color);
	link("viewRect", viewRect, true, false);
	if(font)
	{
		textColorValue = new Label(0,0,"|", font, root);
		auto pos = getTLPosition();
		textColorValue->setCharSize(22);
		textColorValue->setTLPosition(pos.x, pos.y-textColorValue->getSize().y-5);
		textColorValue->setTextFillColor(sf::Color::Black);
		textColorValue->getText().setOutlineColor(sf::Color::White);
		textColorValue->getText().setOutlineThickness(2);
		textColorValue->setFillColor(sf::Color::Transparent);
		textColorValue->setTextWithoutChange(std::to_string(color.r)+" "+std::to_string(color.g)+" "+std::to_string(color.b)+" "+std::to_string(color.a));
		link("ztextColorValue", *textColorValue, true, true);
	}
	trace("ColorPicker created");
}

ColorPicker::~ColorPicker()
{
	trace("ColorPicker deleted");
}

void ColorPicker::setMainColor(const sf::Color& color)
{
	sf::Image img = colorPickerTxtr->copyToImage();
	//std::cout << (int)color.r << " " <<(int) color.g << " " << (int)color.b << " " << color.a << std::endl;
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			int r, g, b, a = color.a;
			r = color.r + (255 - j);
			if(r > 255) r = 255;
			r *= ((255 - i) / 255.0);
			g = color.g + (255 - j);
			if(g > 255) g = 255;
			g *= ((255 - i) / 255.0);
			b = color.b + (255 - j);
			if(b > 255) b = 255;
			b *= ((255 - i) / 255.0);
			img.setPixel(j, i, sf::Color(r, g, b, a));
		}
	}
	colorPickerTxtr->update(img);
	auto c = getColorAt(static_cast<sf::Vector2i>(viewRect.getPosition()));
	viewRect.setFillColor(c);
	pickedValue = c;
	if(textColorValue)
	{
		textColorValue->setTextWithoutChange(std::to_string(c.r)+" "+std::to_string(c.g)+" "+std::to_string(c.b)+" "+std::to_string(c.a));
	}
}
