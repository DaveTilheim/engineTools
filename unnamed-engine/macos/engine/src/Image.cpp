#include "Image.hpp"

Image::Image(const sf::Image& cp) : sf::Image(cp)
{

}

Image::Image(const sf::Texture& txtr) : sf::Image(txtr.copyToImage())
{

}

Image::Image(const sf::Texture* txtr) : sf::Image(txtr->copyToImage())
{

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

void Image::light(const sf::Image& reference, const sf::Vector2f& pos, sf::Vector2f lightP, const sf::Vector2f& sizeEntity, float angle, const sf::Vector2f& normPos)
{
	const auto s = getSize();
	const float radius = 100.0f;
	sf::Vector2f scale = sf::Vector2f(sizeEntity.x / s.x, sizeEntity.y / s.y);
	sf::Vector2f lightPos;
	lightPos.x = (lightP.x - normPos.x) * cos(rad(-angle)) - (lightP.y - normPos.y) * sin(rad(-angle)) + normPos.x;
	lightPos.y = (lightP.x - normPos.x) * sin(rad(-angle)) + (lightP.y - normPos.y) * cos(rad(-angle)) + normPos.y;
	for(int y = 0; y < s.y; y++)
	{
		for(int x = 0; x < s.x; x++)
		{
			sf::Vector2f pixelPos(x * scale.x + pos.x, y * scale.y + pos.y);
			float dist = sqrt((lightPos.x - pixelPos.x) * (lightPos.x - pixelPos.x) + (lightPos.y - pixelPos.y) * (lightPos.y - pixelPos.y));
			float basicFact = 1 - (dist / radius);
			float fact[4];
			float basicPower[4] = {0};
			float luxRgbPower[4] = {1, 1, 1, 1};
			for(int f = 0; f < 4; f++)
			{
				fact[f] = basicPower[f] + basicFact;
				if(fact[f] < basicPower[f]) fact[f] = basicPower[f];
				else if(fact[f] > 1) fact[f] = 1;
			}
			sf::Color px = reference.getPixel(x, y);
			unsigned r = (px.r * fact[0]) * luxRgbPower[0];
			unsigned g = (px.g * fact[1]) * luxRgbPower[1];
			unsigned b = (px.b * fact[2]) * luxRgbPower[2];
			unsigned a = (px.a * fact[3]) * luxRgbPower[3];
			if(r > 255) r = 255;
			if(g > 255) g = 255;
			if(b > 255) b = 255;
			if(a > 255) a = 255;
			setPixel(x, y, sf::Color(r, g, b));
		}
	}
}



