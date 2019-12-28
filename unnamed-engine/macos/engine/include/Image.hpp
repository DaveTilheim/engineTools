#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <math.h>
#include "Entity.hpp"
#include "Utils.hpp"
#include <functional>

class Image;

class Light
{
private:
	float radius;
	float basicPower[4];
	float luxRgbPower[4];
public:
	Light() : radius(100)
	{
		for(int i = 0; i < 4; i++)
		{
			basicPower[i] = 0;
			luxRgbPower[i] = 1;
		}
	}
	void setRadius(float r)
	{
		radius = r;
	}
	void setBasic(float b1, float b2, float b3, float b4=0)
	{
		basicPower[0] = b1;basicPower[1] = b2;basicPower[2] = b3; basicPower[3]=b4;
	}
	void setLux(float l1, float l2, float l3, float l4=1)
	{
		luxRgbPower[0] = l1;luxRgbPower[1] = l2;luxRgbPower[2] = l2;luxRgbPower[3] = l4;
	}
	friend class Image;
};

class Image final : public sf::Image
{
private:
	string name = "unnamed";
public:
	using sf::Image::Image;
	Image(const sf::Image& cp, string name="unnamed");
	Image(const sf::Texture& txtr, string name="unnamed");
	Image(const sf::Texture* txtr, string name="unnamed");
	Image(float w, float h, const sf::Color& color, string name="unnamed");
	void negative();
	void fade(int filterSize=3);
	void gravity();
	void setName(string name);
	string getName() const;
	void edit(function<void(sf::Color& color)> f);
	template <class T> void light(const sf::Image& reference, const T& entity, const sf::Vector2f lightP, const Light& light)
	{
		sf::Vector2f sc = entity.getScale();
		sf::Vector2f s = static_cast<sf::Vector2f>(getSize());

		sf::Vector2f sizeEntity = sf::Vector2f(1, 1);
		float angle = entity.getRotation();
		if(dynamic_cast<const sf::RectangleShape *>(&entity))
		{
			sizeEntity = dynamic_cast<const sf::RectangleShape *>(&entity)->getSize();
		}
		else if(dynamic_cast<const sf::CircleShape *>(&entity))
		{
			float r = dynamic_cast<const sf::CircleShape *>(&entity)->getRadius();
			sizeEntity = sf::Vector2f(r*2, r*2);
		}
		else //SpriteEntity
		{
			sizeEntity = sf::Vector2f(s.x, s.y);
		}
		sizeEntity.x *= sc.x;
		sizeEntity.y *= sc.y;
		sf::Vector2f scale = sf::Vector2f(sizeEntity.x / s.x, sizeEntity.y / s.y);
		sf::Vector2f lightPos;
		sf::Vector2f normPos = entity.getPosition();
		sf::Vector2f pos = entity.getTLPosition();//entity.getSidePosition(TOP_LEFT);
		pos.x -= entity.getOrigin().x * sc.x - s.x/(s.x / entity.getOrigin().x);
		pos.y -= entity.getOrigin().y * sc.y - s.y/(s.y / entity.getOrigin().y);
		lightPos.x = (lightP.x - normPos.x) * cos(rad(-angle)) - (lightP.y - normPos.y) * sin(rad(-angle)) + normPos.x;
		lightPos.y = (lightP.x - normPos.x) * sin(rad(-angle)) + (lightP.y - normPos.y) * cos(rad(-angle)) + normPos.y;
		for(int y = 0; y < s.y; y++)
		{
			for(int x = 0; x < s.x; x++)
			{
				if(reference.getPixel(x, y).a==0) continue;
				sf::Vector2f pixelPos(x * scale.x + pos.x, y * scale.y + pos.y);
				float dist = sqrt((lightPos.x - pixelPos.x) * (lightPos.x - pixelPos.x) + (lightPos.y - pixelPos.y) * (lightPos.y - pixelPos.y));
				float basicFact = 1 - (dist / light.radius);
				float fact[4];
				for(int f = 0; f < 4; f++)
				{
					fact[f] = light.basicPower[f] + basicFact;
					if(fact[f] < light.basicPower[f]) fact[f] = light.basicPower[f];
					else if(fact[f] > 1) fact[f] = 1;
				}
				sf::Color px = reference.getPixel(x, y);
				unsigned r = (px.r * fact[0]) * light.luxRgbPower[0];
				unsigned g = (px.g * fact[1]) * light.luxRgbPower[1];
				unsigned b = (px.b * fact[2]) * light.luxRgbPower[2];
				unsigned a = (px.a * fact[3]) * light.luxRgbPower[3];
				if(r > 255) r = 255;
				if(g > 255) g = 255;
				if(b > 255) b = 255;
				if(a > 255) a = 255;
				setPixel(x, y, sf::Color(r, g, b));
			}
		}
	}
};

#endif
