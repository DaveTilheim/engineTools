#include "Entity.hpp"

using namespace se;

Entity::Entity(float x, float y, float width, float height, Application *root, sf::Color bgColor) 
: shape(new sf::RectangleShape(sf::Vector2f(width, height))), currentTexture("no-texture"), bgColor(bgColor), root(root)
{
	trace("Entity creation");
	this->shape->setFillColor(this->bgColor);
	this->shape->setPosition(x, y);
}

Entity::Entity(float x, float y, float radius, Application *root, sf::Color bgColor) 
: shape(new sf::CircleShape(radius)), bgColor(bgColor), root(root)
{
	this->shape->setFillColor(this->bgColor);
	this->shape->setPosition(x, y);
	trace("Entity creation");
}

Entity::~Entity()
{
	if(this->getThreadRef())
	{
		this->getThreadRef()->removeByFid(this->getThreadFunctionId());
	}
	for(auto it = this->textures.begin(); it != this->textures.end(); it++)
	{
		delete this->textures[it->first];
	}
	if(this->shape)
	{
		delete this->shape;
	}
	trace("Entity destruction");
}

void Entity::render()
{
	this->root->getWindow()->draw(*this->shape);
}

void Entity::setFillColor(const sf::Color c)
{
	this->shape->setFillColor(c);
}

void Entity::setOutline(const sf::Color &c, float thickness)
{
	this->shape->setOutlineColor(c);
	this->shape->setOutlineThickness(thickness);
}

void Entity::setPosition(float x, float y)
{
	this->shape->setPosition(x, y);
}

void Entity::setRotatePosition(sf::Vector2f ref, float angle, float distance, float originMarginAngle)
{
	this->setPosition(
		ref.x + distance * sin(radians(angle) + radians(originMarginAngle)),
		ref.y - distance * cos(radians(angle) + radians(originMarginAngle))
		);
}


void Entity::setOrigin(float x, float y)
{
	this->shape->setOrigin(x, y);
}

sf::Vector2f Entity::getPosition()
{
	return this->shape->getPosition();
}

sf::Vector2f Entity::getOrigin()
{
	return this->shape->getOrigin();
}

void Entity::movePhy(bool deceleration)
{
	if(deceleration)
	{
		this->updateDeceleration(this->root->getDt());
	}
	else
	{
		this->updateAcceleration(this->root->getDt());
	}
	this->rotatePhy();
	this->move(this->speed.x, this->speed.y);
}

void Entity::movePhy(sf::Vector2f speed, sf::Vector2f target)
{
	sf::Vector2f v = this->getComponent(speed.x,speed.y,target.x,target.y);
	this->setAcceleration(v);
	this->accelerationRotation = (sqrt(v.x*v.x+v.y*v.y))*(v.x < 0 ? -1 : 1)*(v.y < 0 ? -1 : 1 );
	this->movePhy();
}

void Entity::movePhy(sf::Vector2f speed, Entity &target)
{
	sf::Vector2f pos = target.getPosition();
	this->movePhy(speed, pos);
}


void Entity::moveGrav(Entity &other)
{
	this->movePhy(sf::Vector2f(other.gravity, other.gravity), other.getPosition());
}

void Entity::moveGrav(std::vector<Entity *> &others)
{
	int size = others.size();
	this->setAcceleration(sf::Vector2f(0,0));
	for(int i = 0; i < size; i++)
	{
		if(this != others[i])
		{
			sf::Vector2f pos = others[i]->getPosition();
			sf::Vector2f a = this->getComponent(others[i]->gravity, others[i]->gravity, pos.x, pos.y);
			this->acceleration.x += a.x;
			this->acceleration.y += a.y;
			this->accelerationRotation += (sqrt(a.x*a.x+a.y*a.y))*(a.x < 0 ? -1 : 1)*(a.y < 0 ? -1 : 1 );
			this->updateAccelerationRotation(this->root->getDt());
			this->updateAcceleration(this->root->getDt());
		}
	}
	this->movePhy();
}

void Entity::movePhy(std::vector<Entity *> &others, float metreAsPixel)
{
	int size = others.size();
	this->setAcceleration(sf::Vector2f(0,0));
	for(int i = 0; i < size; i++)
	{
		if(this != others[i])
		{
			sf::Vector2f dc = this->getDistanceComponent(*others[i], metreAsPixel);
			float d = this->getDistance(*others[i], metreAsPixel);
			sf::Vector2f force(0,0);
			if(d)
			{
				force.x = ((G * this->mass * others[i]->mass) / (d*d)) * (dc.x < 0 ? -1 : 1);
				force.y = ((G * this->mass * others[i]->mass) / (d*d)) * (dc.y < 0 ? -1 : 1);
			}
			else
			{
				force.x = 0;
				force.y = 0;
			}
			this->acceleration.x += force.x / this->mass;
			this->acceleration.y += force.y / this->mass;
			this->updateAcceleration(this->root->getDt());
			this->accelerationRotation += (sqrt(force.x*force.x+force.y*force.y)* (dc.x < 0 ? -1 : 1)* (dc.y < 0 ? -1 : 1)) / this->mass;
			this->updateAccelerationRotation(this->root->getDt());
		}
	}
	this->movePhy();
}

void Entity::movePhy(Entity &other, float metreAsPixel)
{
	sf::Vector2f dc = this->getDistanceComponent(other, metreAsPixel);
	float d = this->getDistance(other, metreAsPixel);
	sf::Vector2f force(0,0);
	if(d)
	{
		force.x = ((G * this->mass * other.mass) / (d*d)) * (dc.x < 0 ? -1 : 1);
		force.y = ((G * this->mass * other.mass) / (d*d)) * (dc.y < 0 ? -1 : 1);
	}
	else
	{
		force.x = 0;
		force.y = 0;
	}
	this->acceleration.x += force.x / this->mass;
	this->acceleration.y += force.y / this->mass;
	this->accelerationRotation = (sqrt(force.x*force.x+force.y*force.y)* (dc.x < 0 ? -1 : 1)* (dc.y < 0 ? -1 : 1)) / this->mass;
	this->updateAccelerationRotation(this->root->getDt());
	this->movePhy();
}

void Entity::move(float vx, float vy)
{
	vx *= this->root->getDt();
	vy *= this->root->getDt();
	this->shape->move(vx, vy);
}

void Entity::move(float vx, float vy, float timesec)
{
	vx /= timesec;
	vy /= timesec;
	this->move(vx, vy);
}

void Entity::move(float vx, float vy, float timesecx, float timesecy)
{
	vx /= timesecx;
	vy /= timesecy;
	this->move(vx, vy);
}

sf::Vector2f Entity::getComponent(float vx, float vy, float x, float y)
{
	sf::Vector2f pos = this->getPosition();
	float distance = this->getDistance(sf::Vector2f(x, y));
	if(distance)
		return sf::Vector2f(sin((x - pos.x) / distance) * vx, sin((y - pos.y) / distance) * vy);
	return sf::Vector2f(0,0);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY)
{
	sf::Vector2f pos = this->getMiddle();
	float distance = this->getDistance(sf::Vector2f(targetX, targetY));
	if(distance)
		this->move(sin((targetX - pos.x) / distance) * vx, sin((targetY - pos.y) / distance) * vy);
}

void Entity::moveTowardDistRel(float vx, float vy, float targetX, float targetY)
{
	sf::Vector2f pos = this->getMiddle();
	this->move((targetX - pos.x) * vx,(targetY - pos.y) * vy);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY, float timesec)
{
	vx /= timesec;
	vy /= timesec;
	this->moveToward(vx, vy, targetX, targetY);
}

void Entity::moveToward(float vx, float vy, float targetX, float targetY, float timesecx, float timesecy)
{
	vx /= timesecx;
	vy /= timesecy;
	this->moveToward(vx, vy, targetX, targetY);
}

void Entity::moveToward(float vx, float vy, Entity &other)
{
	sf::Vector2f pos = other.getPosition();
	this->moveToward(vx, vy, pos.x, pos.y);
}

void Entity::moveToward(float vx, float vy, Entity &other, float timesec)
{
	sf::Vector2f pos = other.getPosition();
	this->moveToward(vx, vy, pos.x, pos.y, timesec);
}

void Entity::moveToward(float vx, float vy, Entity &other, float timesecx, float timesecy)
{
	sf::Vector2f pos = other.getPosition();
	this->moveToward(vx, vy, pos.x, pos.y, timesecx, timesecy);
}

float Entity::getDistance(sf::Vector2f point, float metreAsPixel)
{
	const sf::Vector2f& middle = this->getMiddle();
	return sqrt((point.x - middle.x)*(point.x - middle.x) + (point.y - middle.y)*(point.y - middle.y)) * metreAsPixel;
}

float Entity::getDistance(Entity& other, float metreAsPixel)
{
	return this->getDistance(other.getMiddle(), metreAsPixel);
}

sf::Vector2f Entity::getDistanceComponent(sf::Vector2f point, float metreAsPixel)
{
	sf::Vector2f pos = this->getPosition();
	return sf::Vector2f((point.x - pos.x) * metreAsPixel, (point.y - pos.y) * metreAsPixel);
}

sf::Vector2f Entity::getDistanceComponent(Entity& other, float metreAsPixel)
{
	sf::Vector2f pos = other.getPosition();
	return this->getDistanceComponent(pos, metreAsPixel);
}

float Entity::getRotation()
{
	return this->shape->getRotation();
}

float Entity::getRotation(float x, float y)
{
	sf::Vector2f pos = this->getPosition();
	return degres(atan2(-(pos.y-y), -(pos.x-x)));
}

void Entity::setRotation(float angle)
{
	this->shape->setRotation(angle);
}

void Entity::setRotation(float targetX, float targetY)
{
	sf::Vector2f pos = this->getPosition();
	float angle = degres(atan2(-(pos.y-targetY), -(pos.x-targetX)));
	this->setRotation(angle);
}

void Entity::setRotation(Entity &other)
{
	sf::Vector2f pos = other.getPosition();
	this->setRotation(pos.x, pos.y);
}

void Entity::rotation(float angle)
{
	this->setRotation(this->getRotation() + angle);
}

void Entity::rotateToward(float va, float x, float y)
{
	
}

void Entity::rotatePhy(bool deceleration)
{
	if(deceleration)
	{
		this->updateDecelerationRotation(this->root->getDt());
	}
	else
	{
		this->updateAccelerationRotation(this->root->getDt());
	}
	this->rotate(this->speedRotation);
}
//phy
void Entity::rotateWithDist(float angle, sf::Vector2f target, float d)
{
	this->speedRotation += angle * this->root->getDt();
	this->setRotatePosition(target, this->speedRotation, d);
}

void Entity::rotate(float angle)
{
	angle *= this->root->getDt();
	this->shape->rotate(angle);
}

void Entity::rotate(float angle, float timesec)
{
	angle /= timesec;
	this->rotate(angle);
}

void Entity::rotate(float angle, float targetX, float targetY)
{
	angle *= this->root->getDt();
	angle = radians(angle);
	sf::Vector2f pos = this->getPosition();
	this->setPosition(pos.x-targetX, pos.y-targetY);
	pos = this->getPosition();
	this->setPosition(cos(angle) * pos.x - sin(angle) * pos.y,
					  sin(angle) * pos.x + cos(angle) * pos.y);
	pos = this->getPosition();
	this->setPosition(pos.x+targetX, pos.y+targetY);
}

void Entity::rotate(float angle, float targetX, float targetY, float timesec)
{
	angle /= timesec;
	this->rotate(angle, targetX, targetY);
}

void Entity::rotate(float angle, Entity &other)
{
	sf::Vector2f otherPos = other.getPosition();
	this->rotate(angle, otherPos.x, otherPos.y);
}

void Entity::rotate(float angle, Entity &other, float timesec)
{
	sf::Vector2f otherPos = other.getPosition();
	this->rotate(angle, otherPos.x, otherPos.y, timesec);
}

void Entity::spirale(float vx, float vy, float angle, float targetX, float targetY)
{
	this->rotate(angle, targetX, targetY);
	this->moveToward(vx, vy, targetX, targetY);
}

void Entity::spiraleDistRel(float vx, float vy, float angle, float targetX, float targetY)
{
	this->rotate(angle, targetX, targetY);
	this->moveTowardDistRel(vx, vy, targetX, targetY);
}


void Entity::spirale(float vx, float vy, float angle, float targetX, float targetY, float timesec)
{
	this->rotate(angle, targetX, targetY, timesec);
	this->moveToward(vx, vy, targetX, targetY, timesec);
}

void Entity::spirale(float vx, float vy, float angle, float targetX, float targetY, float timeseca, float timesecx, float timesecy)
{
	this->rotate(angle, targetX, targetY, timeseca);
	this->moveToward(vx, vy, targetX, targetY, timesecx, timesecy);
}


void Entity::spirale(float vx, float vy, float angle, Entity &other)
{
	sf::Vector2f pos = other.getPosition();
	this->rotate(angle, pos.x, pos.y);
	this->moveToward(vx, vy, pos.x, pos.y);
}


void Entity::spirale(float vx, float vy, float angle, Entity &other, float timesec)
{
	sf::Vector2f pos = other.getPosition();
	this->rotate(angle, pos.x, pos.y, timesec);
	this->moveToward(vx, vy, pos.x, pos.y, timesec);
}

void Entity::spirale(float vx, float vy, float angle, Entity &other, float timeseca, float timesecx, float timesecy)
{
	sf::Vector2f pos = other.getPosition();
	this->rotate(angle, pos.x, pos.y, timeseca);
	this->moveToward(vx, vy, pos.x, pos.y, timesecx, timesecy);
}

void Entity::spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spirale(vx, vy, angle, targetX, targetY);
	}
	else
	{
		this->rotate(angle, targetX, targetY);
	}
}

void Entity::spiraleLimitDistRel(float vx, float vy, float angle, float targetX, float targetY, float limit)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spiraleDistRel(vx, vy, angle, targetX, targetY);
	}
	else
	{
		this->rotate(angle, targetX, targetY);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit, float timesec)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spirale(vx, vy, angle, targetX, targetY, timesec);
	}
	else
	{
		this->rotate(angle, targetX, targetY, timesec);
	}
}


void Entity::spiraleLimit(float vx, float vy, float angle, float targetX, float targetY, float limit, float timeseca, float timesecx, float timesecy)
{
	if(this->getDistance(sf::Vector2f(targetX, targetY)) > limit)
	{
		this->spirale(vx, vy, angle, targetX, targetY, timeseca, timesecx, timesecy);
	}
	else
	{
		this->rotate(angle, targetX, targetY, timeseca);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, Entity &other, float limit)
{
	if(this->getDistance(other) > limit)
	{
		this->spirale(vx, vy, angle, other);
	}
	else
	{
		this->rotate(angle, other);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, Entity &other, float limit, float timesec)
{
	if(this->getDistance(other) > limit)
	{
		this->spirale(vx, vy, angle, other, timesec);
	}
	else
	{
		this->rotate(angle, other, timesec);
	}
}

void Entity::spiraleLimit(float vx, float vy, float angle, Entity &other, float limit, float timeseca, float timesecx, float timesecy)
{
	if(this->getDistance(other) > limit)
	{
		this->spirale(vx, vy, angle, other, timeseca, timesecx, timesecy);
	}
	else
	{
		this->rotate(angle, other, timeseca);
	}
}

void Entity::addTexture(std::string name, std::string filename)
{
	sf::Texture *txtr = new sf::Texture();
	txtr->loadFromFile(filename);
	this->textures[name] = txtr;
}

void Entity::setTexture(std::string name)
{
	if(name.size())
	{
		this->shape->setTexture(this->textures[name]);
		this->currentTexture = name;
	}
	else
	{
		this->shape->setTexture(nullptr);
		this->currentTexture = "no-texture";
	}
}


void Entity::spriteAnimation(std::string nameprefix, unsigned max)
{
	unsigned it = std::atoi(this->currentTexture.substr(nameprefix.size()).c_str());
	this->setTexture(nameprefix + std::to_string((it + 1) % (max+1)));
}

void Entity::spriteAnimation(std::string nameprefix, unsigned max, float timesec)
{
	if(++this->spriteAnimationCounter >= this->root->getFrameRate() * timesec)
	{
		unsigned it = std::atoi(this->currentTexture.substr(nameprefix.size()).c_str());
		this->setTexture(nameprefix + std::to_string((it + 1) % (max+1)));
		this->spriteAnimationCounter = 0;
	}
}

void Entity::resetSpriteAnimationCounter()
{
	this->spriteAnimationCounter = 0;
}

void Entity::editTexture(std::function<void(sf::Color& c)> transformation, std::string name)
{
	sf::Image image;
	if(name.size() == 0)
	{
		name = this->currentTexture;
	}
	sf::Texture *txtr = this->textures[name];
	image = txtr->copyToImage();
	sf::Vector2u siz = image.getSize();
	for(int i = 0; i < siz.x; i++)
	{
		for(int j = 0; j < siz.y; j++)
		{
			sf::Color c = image.getPixel(i, j);
			transformation(c);
			image.setPixel(i, j, c);
		}
	}
	txtr->loadFromImage(image);
}

void Entity::editTexture(std::function<void(sf::Image& c)> transformation, std::string name)
{
	sf::Image image;
	if(name.size() == 0)
	{
		name = this->currentTexture;
	}
	sf::Texture *txtr = this->textures[name];
	image = txtr->copyToImage();
	transformation(image);
	txtr->loadFromImage(image);
}

bool Entity::textureIs(std::function<bool(const sf::Color& c)> checking, std::function<bool(unsigned truecptr, unsigned falsecptr)> boolres, std::string name)
{
	sf::Image image;
	if(name.size() == 0)
	{
		name = this->currentTexture;
	}
	sf::Texture *txtr = this->textures[name];
	image = txtr->copyToImage();
	sf::Vector2u siz = image.getSize();
	unsigned truecptr = 0, falsecptr = 0;
	for(int i = 0; i < siz.x; i++)
	{
		for(int j = 0; j < siz.y; j++)
		{
			checking(image.getPixel(i, j)) ? ++truecptr : ++falsecptr;
		}
	}
	return boolres(truecptr, falsecptr);
}

bool Entity::basicIntersects(const Entity &e) const
{
	return this->shape->getGlobalBounds().intersects(e.shape->getGlobalBounds());
}


bool Entity::contains(sf::Vector2f point) const
{
	return this->shape->getGlobalBounds().contains(point);
}

bool Entity::pixelIntersects(Entity &e, unsigned incX, unsigned incY)
{
	if(this->basicIntersects(e))
	{
		sf::Image thisImg = this->shape->getTexture()->copyToImage();
		sf::Image otherImg = e.shape->getTexture()->copyToImage();
		sf::Vector2u otherSize = otherImg.getSize();
		sf::Rect<float> otherRect = e.shape->getGlobalBounds();
		sf::Rect<float> thisRect = this->shape->getGlobalBounds();
		for(int i = 0; i < otherSize.y; i+=incY)
		{
			for(int j = 0; j < otherSize.x; j+=incX)
			{
				sf::Color c = otherImg.getPixel(j, i);
				if(c.a != 0)
				{
					sf::Vector2f pixel(otherRect.left + j, otherRect.top + i);
					if(this->contains(pixel))
					{
						if(thisImg.getPixel(pixel.x - thisRect.left, pixel.y - thisRect.top).a != 0)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Entity::pixelContains(sf::Vector2f point)
{
	if(this->contains(point))
	{
		sf::Image img = this->shape->getTexture()->copyToImage();
		sf::Rect<float> rect = this->shape->getGlobalBounds();
		if(img.getPixel(point.x - rect.left, point.y - rect.top).a != 0)
		{
			return true;
		}
	}
	return false;
}

void Entity::join(Thread &th)
{
	this->setThreadRef(th);
	this->setThreadFunctionId(
		th.add([this]()
		{
			this->update();
	}));
}


