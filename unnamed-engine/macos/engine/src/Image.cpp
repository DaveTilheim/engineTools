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


