#include "Animated.hpp"


float Animated::getAnimationSpeed() const
{
	return animationSpeed;
}

int Animated::getNbSprites() const
{
	return nbSprites;
}

int Animated::getBeginSprite() const
{
	return beginSprite;
}

void Animated::setAnimationSpeed(float aspd)
{
	animationSpeed = aspd;
}

void Animated::setNbSprites(int nb)
{
	nbSprites = nb;
}

void Animated::setBeginSprite(int bs)
{
	beginSprite = bs;
}

void Animated::updateTexture(const Image& img)
{
	if(dynamic_cast<sf::Shape *>(this))
	{
		((sf::Texture *)dynamic_cast<sf::Shape *>(this)->getTexture())->update(img);
	}
	else if(dynamic_cast<sf::Sprite *>(this))
	{
		((sf::Texture *)dynamic_cast<sf::Sprite *>(this)->getTexture())->update(img);
	}
}

void Animated::replaceTexture(const Image& img)
{
	if(dynamic_cast<sf::Shape *>(this))
	{
		*((sf::Texture *)dynamic_cast<sf::Shape *>(this)->getTexture()) = sf::Texture();
		((sf::Texture *)dynamic_cast<sf::Shape *>(this)->getTexture())->loadFromImage(img);
		auto s = ((sf::Texture *)dynamic_cast<sf::Shape *>(this)->getTexture())->getSize();
		dynamic_cast<sf::Shape *>(this)->setTextureRect(sf::Rect<int>(0,0,s.x,s.y));
	}
	else if(dynamic_cast<sf::Sprite *>(this))
	{
		*((sf::Texture *)dynamic_cast<sf::Sprite *>(this)->getTexture()) = sf::Texture();
		((sf::Texture *)dynamic_cast<sf::Sprite *>(this)->getTexture())->loadFromImage(img);
		auto s = ((sf::Texture *)dynamic_cast<sf::Sprite *>(this)->getTexture())->getSize();
		dynamic_cast<sf::Sprite *>(this)->setTextureRect(sf::Rect<int>(0,0,s.x,s.y));
	}
}

void Animated::updateSprite()
{
	sf::Vector2u s;
	sf::Rect<int> rect;
	if(dynamic_cast<sf::Shape *>(this))
	{
		s = dynamic_cast<sf::Shape *>(this)->getTexture()->getSize();
		rect = dynamic_cast<sf::Shape *>(this)->getTextureRect();
	}
	else if(dynamic_cast<sf::Sprite *>(this))
	{
		s = dynamic_cast<sf::Sprite *>(this)->getTexture()->getSize();
		rect = dynamic_cast<sf::Sprite *>(this)->getTextureRect();
	}
	if(getNbSprites() and (rect.left / rect.width) + (rect.top / rect.height) * (s.x / rect.width) + 1 >= getNbSprites() + getBeginSprite())
	{
		updateSprite(getBeginSprite());
	}
	else
	{
		if(rect.left + rect.width >= s.x or s.x - (rect.left + rect.width) < rect.width)
		{
			rect.left = 0;
			if(rect.top + rect.height >= s.y or s.y - (rect.top + rect.height) < rect.height) rect.top = 0;
			else rect.top += rect.height;
		}
		else rect.left += rect.width;
		if(dynamic_cast<sf::Shape *>(this))
		{
			dynamic_cast<sf::Shape *>(this)->setTextureRect(rect);
		}
		else if(dynamic_cast<sf::Sprite *>(this))
		{
			dynamic_cast<sf::Sprite *>(this)->setTextureRect(rect);
		}
	}

}

void Animated::updateSprite(int index)
{
	sf::Vector2u s;
	sf::Rect<int> rect;
	if(dynamic_cast<sf::Shape *>(this))
	{
		s = dynamic_cast<sf::Shape *>(this)->getTexture()->getSize();
		rect = dynamic_cast<sf::Shape *>(this)->getTextureRect();
	}
	else if(dynamic_cast<sf::Sprite *>(this))
	{
		s = dynamic_cast<sf::Sprite *>(this)->getTexture()->getSize();
		rect = dynamic_cast<sf::Sprite *>(this)->getTextureRect();
	}
	rect.left = (index * rect.width) % s.x;
	rect.top = (index / (s.x / rect.width)) *rect.height;
	if(dynamic_cast<sf::Shape *>(this))
	{
		dynamic_cast<sf::Shape *>(this)->setTextureRect(rect);
	}
	else if(dynamic_cast<sf::Sprite *>(this))
	{
		dynamic_cast<sf::Sprite *>(this)->setTextureRect(rect);
	}
}

void Animated::animate()
{
	if(animationClock.getElapsedTime().asMilliseconds() >= getAnimationSpeed() * 1000.0)
	{
		updateSprite();
		animationClock.restart();
	}
}


void Animated::setAnimationOptions(float as, int nbs, int bs)
{
	setAnimationSpeed(as);
	setNbSprites(nbs);
	setBeginSprite(bs);
}

void Animated::setSpriteSize(int w, int h)
{
	sf::Rect<int> rect;
	sf::Vector2u txtrSize;
	if(dynamic_cast<sf::Shape *>(this))
	{
		rect = dynamic_cast<sf::Shape *>(this)->getTextureRect();
		txtrSize = dynamic_cast<sf::Shape *>(this)->getTexture()->getSize();
		rect.width = txtrSize.x / w;
		rect.height = txtrSize.y / h;
		dynamic_cast<sf::Shape *>(this)->setTextureRect(rect);
	}
	else if(dynamic_cast<sf::Sprite *>(this))
	{
		rect = dynamic_cast<sf::Sprite *>(this)->getTextureRect();
		txtrSize = dynamic_cast<sf::Sprite *>(this)->getTexture()->getSize();
		rect.width = txtrSize.x / w;
		rect.height = txtrSize.y / h;
		dynamic_cast<sf::Sprite *>(this)->setTextureRect(rect);
	}
}
