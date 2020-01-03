#include "Image.hpp"

Image::Image(const sf::Image& cp, string name) : sf::Image(cp), name(name)
{

}

Image::Image(float w, float h, const sf::Color& color, string name) : sf::Image(), name(name)
{
	create(w, h, color);
}

Image::Image(const sf::Texture& txtr, string name) : sf::Image(txtr.copyToImage()), name(name)
{

}

Image::Image(const sf::Texture* txtr, string name) : sf::Image(txtr->copyToImage()), name(name)
{

}

void Image::setName(string nam)
{
	name = nam;
}

string Image::getName() const
{
	return name;
}

void Image::negative()
{
	auto s = getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			px.r = 255 - px.r;
			px.g = 255 - px.g;
			px.b = 255 - px.b;
			setPixel(x, y, px);
		}
	}
}

void Image::fade(int filterSize)
{
	auto s = getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			int moy[3] = {0};
			int cptr = 0;
			for(int ymoy = y-filterSize/2; ymoy <= y+filterSize/2; ymoy++)
			{
				if(ymoy >= 0 and ymoy <= s.y)
				{
					for(int xmoy = x-filterSize/2; xmoy <= x+filterSize/2; xmoy++)
					{
						if(xmoy >= 0 and xmoy <= s.x)
						{
							auto px = getPixel(xmoy, ymoy);
							moy[0] += px.r;
							moy[1] += px.g;
							moy[2] += px.b;
							cptr++;
						}
					}
				}
			}
			moy[0] /= cptr;
			moy[1] /= cptr;
			moy[2] /= cptr;
			setPixel(x, y, sf::Color(moy[0], moy[1], moy[2]));
		}
	}
}


void Image::gravity()
{
	auto s = getSize();
	for(int y = s.y-1; y >= 0; y--)
	{
		for(int x = s.x-1; x >= 0; x--)
		{
			sf::Color px = getPixel(x, y);
			if(px.a)
			{
				if(getPixel(x, y+1).a == 0)
				{
					setPixel(x, y+1, px);
					setPixel(x, y, sf::Color::Transparent);
				}
			}
		}
	}
}

void Image::edit(function<void(sf::Color& color)> f)
{
	auto s = getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			f(px);
			setPixel(x, y, px);
		}
	}
}

void Image::edit(const sf::Image& filter, function<void(sf::Color& color, const sf::Color& filter)> f)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			f(px, fpx);
			setPixel(x, y, px);
		}
	}
}

void Image::applyAndFilter(const sf::Image& filter)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			if(px.a and fpx.a)
			{
				setPixel(x, y, sf::Color(px.r & fpx.r, px.g & fpx.g, px.b & fpx.b));
			}
		}
	}
}

void Image::applyOrFilter(const sf::Image& filter)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			if(px.a and fpx.a)
			{
				setPixel(x, y, sf::Color(px.r | fpx.r, px.g | fpx.g, px.b | fpx.b));
			}
		}
	}
}

void Image::applyAddFilter(const sf::Image& filter)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			if(px.a and fpx.a)
			{
				if(px.r + fpx.r > 255) px.r = 255;
				else px.r += fpx.r;
				if(px.g + fpx.g > 255) px.g = 255;
				else px.g += fpx.g;
				if(px.b + fpx.b > 255) px.b = 255;
				else px.b += fpx.b;
				setPixel(x, y, px);
			}
		}
	}
}

void Image::applySubFilter(const sf::Image& filter)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			if(px.a and fpx.a)
			{
				if(px.r - fpx.r < 0) px.r = 0;
				else px.r -= fpx.r;
				if(px.g - fpx.g < 0) px.g = 0;
				else px.g -= fpx.g;
				if(px.b - fpx.b < 0) px.b = 0;
				else px.b -= fpx.b;
				setPixel(x, y, px);
			}
		}
	}
}

void Image::applyTotalFilter(const sf::Image& filter)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			if(px.a and fpx.a)
			{
				setPixel(x, y, fpx);
			}
		}
	}
}

void Image::applyMoyFilter(const sf::Image& filter)
{
	auto s = getSize();
	auto fs = filter.getSize();
	auto scale = sf::Vector2f(fs.x / s.x, fs.y / s.y);
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			sf::Color fpx = filter.getPixel(x * scale.x, y * scale.y);
			if(px.a and fpx.a)
			{
				px.r = (px.r + fpx.r) / 2;
				px.g = (px.g + fpx.g) / 2;
				px.b = (px.b + fpx.b) / 2;
				setPixel(x, y, px);
			}
		}
	}
}

void Image::luminus(int l)
{
	auto s = getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			if(px.r + l > 255) px.r = 255;
			else if(px.r + l < 0) px.r = 0;
			else px.r += l;
			if(px.g + l > 255) px.g = 255;
			else if(px.g + l < 0) px.g = 0;
			else px.g += l;
			if(px.b + l > 255) px.b = 255;
			else if(px.b + l < 0) px.b = 0;
			else px.b += l;
			setPixel(x, y, px);
		}
	}
}

void Image::limit(unsigned char limit, const sf::Color& c, bool up)
{
	auto s = getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = getPixel(x, y);
			if(px.a)
			{
				if(not up and (px.r + px.g + px.b) / 3 < limit)
				{
					px = c;
					setPixel(x, y, px);
				}
				else if(up and (px.r + px.g + px.b) / 3 > limit)
				{
					px = c;
					setPixel(x, y, px);
				}
			}
		}
	}
}

Image Image::combine(const sf::Image& image, bool xaxis)
{
	auto s = getSize();
	auto others = image.getSize();
	sf::Vector2u newSize;
	Image out;
	if(xaxis)
	{
		newSize.x = s.x + others.x;
		newSize.y = s.y >= others.y ? s.y : others.y;
		out.create(newSize.x, newSize.y);
		out.copy(*this, 0, 0);
		out.copy(image, s.x, 0);
	}
	else
	{
		newSize.y = s.y + others.y;
		newSize.x = s.x >= others.x ? s.x : others.x;
		out.create(newSize.x, newSize.y);
		out.copy(*this, 0, 0);
		out.copy(image, 0, s.y);
	}
	return out;
}

Image Image::extract(int nw, int nh, int beg, int end)
{
	Image tmp;
	int nbSprites = end - beg;
	sf::Vector2u s = getSize();
	sf::Rect<int> rect;
	rect.width = s.x / nw;
	rect.height = s.y / nh;
	tmp.create(nbSprites * rect.width, rect.height);
	for(int i = 0; i < nbSprites; i++)
	{
		int index = beg + i;
		rect.left = (index * rect.width) % s.x;
		rect.top = (index / (s.x / rect.width)) * rect.height;
		tmp.copy(*this, i * rect.width, 0, rect);
	}
	return tmp;
}

Image& Image::operator<<(const sf::Image& other)
{
	applyMoyFilter(other);
	return *this;
}

Image& Image::operator<<(const sf::Texture* other)
{
	Image tmp(other);
	applyMoyFilter(tmp);
	return *this;
}

Image Image::operator&(const sf::Image& other)
{
	Image tmp(*this);
	tmp.applyAndFilter(other);
	return tmp;
}

Image Image::operator|(const sf::Image& other)
{
	Image tmp(*this);
	tmp.applyOrFilter(other);
	return tmp;
}

Image Image::operator+(const sf::Image& other)
{
	Image tmp(*this);
	tmp.applyAddFilter(other);
	return tmp;
}

Image Image::operator-(const sf::Image& other)
{
	Image tmp(*this);
	tmp.applySubFilter(other);
	return tmp;
}

Image Image::operator+(int l)
{
	Image tmp(*this);
	tmp.luminus(l);
	return tmp;
}

Image Image::operator-(int l)
{
	Image tmp(*this);
	tmp.luminus(-l);
	return tmp;
}

Image& Image::operator++()
{
	luminus(1);
	return *this;
}

Image& Image::operator--()
{
	luminus(-1);
	return *this;
}

Image Image::operator++(int)
{
	Image tmp(*this);
	luminus(1);
	return tmp;
}

Image Image::operator--(int)
{
	Image tmp(*this);
	luminus(-1);
	return tmp;
}

Image Image::operator~()
{
	Image tmp(*this);
	tmp.negative();
	return tmp;
}

Image Image::neg(const sf::Image& img)
{
	Image i(img);
	auto s = i.getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = i.getPixel(x, y);
			px.r = 255 - px.r;
			px.g = 255 - px.g;
			px.b = 255 - px.b;
			i.setPixel(x, y, px);
		}
	}
	return i;
}

Image Image::neg(const sf::Texture* txtr)
{
	Image i(txtr);
	auto s = i.getSize();
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Color px = i.getPixel(x, y);
			px.r = 255 - px.r;
			px.g = 255 - px.g;
			px.b = 255 - px.b;
			i.setPixel(x, y, px);
		}
	}
	return i;
}

void Image::light(const sf::Image& reference, const sf::Vector2f lightPos, const Light& light)
{
	
	auto s = getSize();
	
	sf::Vector2f pos = sf::Vector2f(0,0);
	
	for(int y = 0; y < s.y; y+=light.jump)
	{
		for(int x = 0; x < s.x; x+=light.jump)
		{
			sf::Vector2f pixelPos(x + pos.x,  y + pos.y);
			float dist = sqrt((lightPos.x - pixelPos.x) * (lightPos.x - pixelPos.x) + (lightPos.y - pixelPos.y) * (lightPos.y - pixelPos.y));
			sf::Color px = reference.getPixel(x, y);
			float basicFact = light.fading - (dist / light.radius);
			float fact[4];
			for(int f = 0; f < 4; f++)
			{
				fact[f] = light.basicPower[f] + basicFact;
				if(fact[f] < light.basicPower[f]) fact[f] = light.basicPower[f];
				else if(fact[f] > 1) fact[f] = 1;
			}
			unsigned r = (px.r * fact[0]) * light.luxRgbPower[0];
			unsigned g = (px.g * fact[1]) * light.luxRgbPower[1];
			unsigned b = (px.b * fact[2]) * light.luxRgbPower[2];
			unsigned a = (px.a * fact[3]) * light.luxRgbPower[3];
			if(r > 255) r = 255;
			if(g > 255) g = 255;
			if(b > 255) b = 255;
			if(a > 255) a = 255;
			for(int i = y; i < y + light.jump and i < s.y; i++)
			{
				for(int j = x; j < x + light.jump and j < s.x; j++)
				{
					setPixel(j, i, sf::Color(r, g, b, a));
				}
			}
		}
	}
}

void Image::pixelize(int jump)
{
	auto s = getSize();
	
	sf::Vector2f pos = sf::Vector2f(0,0);
	
	for(int y = 0; y < s.y; y+=jump)
	{
		for(int x = 0; x < s.x; x+=jump)
		{
			auto px = getPixel(x, y);
			for(int i = y; i < y + jump and i < s.y; i++)
			{
				for(int j = x; j < x + jump and j < s.x; j++)
				{
					setPixel(j, i, px);
				}
			}
		}
	}
}


