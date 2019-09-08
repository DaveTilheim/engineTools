#include "Line.hpp"

using namespace se;

Line::Line(sf::Vector2f start, sf::Vector2f end, float weight, Application *root, sf::Color bgColor)
 : RectEntity(start.x, start.y, 1, 1, root, bgColor), start(start), end(end), weight(weight)
{
	this->setSize(sf::Vector2f(this->getDistance(this->end), this->weight));
	this->setOrigin(0, weight / 2.0);
	this->setRotation(this->end.x, this->end.y);
}

void Line::setStart(sf::Vector2f pos)
{
	this->start = pos;
	this->setPosition(pos.x, pos.y);
	this->setSize(sf::Vector2f(this->getDistance(this->end), this->weight));
	this->setRotation(this->end.x, this->end.y);
}

void Line::setEnd(sf::Vector2f pos)
{
	this->end = pos;
	this->setSize(sf::Vector2f(this->getDistance(this->end), this->weight));
	this->setRotation(this->end.x, this->end.y);
}

float Line::getDistance(sf::Vector2f point, float metreAsPixel)
{
	return sqrt((point.x - start.x)*(point.x - start.x) + (point.y - start.y)*(point.y - start.y)) * metreAsPixel;
}

float Line::getDistance(Entity& other, float metreAsPixel)
{
	return this->getDistance(other.getPosition(), metreAsPixel);
}
