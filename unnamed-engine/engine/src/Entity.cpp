#include "Entity.hpp"


template <class T> Entity<T>::Entity() : SystemEntity(), T()
{
	trace("entity creation");
}

template <class T> Entity<T>::Entity(const Entity<T>& cp) : SystemEntity(cp), T(cp)
{
	speed = cp.speed;
	acceleration = cp.acceleration;
	speedRotation = cp.speedRotation;
	accelerationRotation = cp.accelerationRotation;
	relativeSpeedRotation = cp.relativeSpeedRotation;
	trace("entity creation");
}

template <class T> Entity<T>::~Entity()
{
	trace("entity destruction");
}

template <class T> void Entity<T>::view(sf::RenderWindow& window) const
{
	window.draw(*this);
}

template <class T> void Entity<T>::setRotatePosition(float x, float y, Degre angle, float distance)
{
	T::setPosition(
		x + distance * sin(rad(angle)),
		y - distance * cos(rad(angle))
	);
}

template <class T> void Entity<T>::setRotatePosition(const sf::Vector2f& ref, Degre angle, float distance)
{
	T::setPosition(
		ref.x + distance * sin(rad(angle)),
		ref.y - distance * cos(rad(angle))
	);
}

template <class T> void Entity<T>::setSideOrigin(Origin origin)
{
	auto rect = T::getGlobalBounds();
	rect.width /= T::getScale().x;
	rect.height /= T::getScale().y;
	switch(origin)
	{
		case TOP_LEFT: T::setOrigin(0, 0); break;
		case TOP_CENTER: T::setOrigin(rect.width / 2, 0); break;
		case TOP_RIGHT: T::setOrigin(rect.width, 0); break;
		case BOTTOM_LEFT: T::setOrigin(0, rect.height); break;
		case BOTTOM_CENTER: T::setOrigin(rect.width / 2.0, rect.height); break;
		case BOTTOM_RIGHT: T::setOrigin(rect.width, rect.height); break;
		case MIDDLE_LEFT: T::setOrigin(0, rect.height / 2); break;
		case MIDDLE_CENTER: T::setOrigin(rect.width / 2, rect.height / 2); break;
		case MIDDLE_RIGHT: T::setOrigin(rect.width, rect.height / 2); break;
	}
}

template <class T> void Entity<T>::setSpeed(float vx, float vy)
{
	speed.x = vx;
	speed.y = vy;
}

template <class T> void Entity<T>::setSpeed(const sf::Vector2f& v)
{
	speed.x = v.x;
	speed.y = v.y;
}

template <class T> void Entity<T>::setAcceleration(float ax, float ay)
{
	acceleration.x = ax;
	acceleration.y = ay;
}

template <class T> void Entity<T>::setAcceleration(const sf::Vector2f& a)
{
	acceleration.x = a.x;
	acceleration.y = a.y;
}

template <class T> void Entity<T>::setSpeedRotation(Degre vr)
{
	speedRotation = vr;
}

template <class T> void Entity<T>::setAccelerationRotation(Degre ar)
{
	accelerationRotation = ar;
}

template <class T> void Entity<T>::setRelativeRotation(float x, float y)
{
	T::setRotation(getRelativeRotation(x, y));
}

template <class T> void Entity<T>::setRelativeRotation(const sf::Vector2f& p)
{
	T::setRotation(getRelativeRotation(p.x, p.y));
}

template <class T> sf::Vector2f Entity<T>::getSpeed() const
{
	return speed;
}

template <class T> sf::Vector2f Entity<T>::getAcceleration() const
{
	return acceleration;
}

template <class T> Degre Entity<T>::getSpeedRotation() const
{
	return speedRotation;
}

template <class T> Degre Entity<T>::getAccelerationRotation() const
{
	return accelerationRotation;
}

template <class T> float Entity<T>::getDistance(float x, float y) const
{
	sf::Vector2f pos = T::getPosition();
	return sqrt((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y));
}

template <class T> float Entity<T>::getDistance(const sf::Vector2f& p) const
{
	sf::Vector2f pos = T::getPosition();
	return sqrt((p.x - pos.x) * (p.x - pos.x) + (p.y - pos.y) * (p.y - pos.y));
}

template <class T> sf::Vector2f Entity<T>::getComponent(float x, float y, float v) const
{
	sf::Vector2f pos = T::getPosition();
	float distance = getDistance(x, y);
	if(distance)
		return sf::Vector2f(((x - pos.x) / distance) * v, ((y - pos.y) / distance) * v);
	return sf::Vector2f(0,0);
}

template <class T> sf::Vector2f Entity<T>::getComponent(const sf::Vector2f& p, float v) const
{
	sf::Vector2f pos = T::getPosition();
	float distance = getDistance(p.x, p.y);
	if(distance)
		return sf::Vector2f(((p.x - pos.x) / distance) * v, ((p.y - pos.y) / distance) * v);
	return sf::Vector2f(0,0);
}

template <class T> Degre Entity<T>::getRelativeRotation(float x, float y) const
{
	sf::Vector2f pos = T::getPosition();
	return deg(atan2(-(pos.y-y), -(pos.x-x)));
}

template <class T> Degre Entity<T>::getRelativeRotation(const sf::Vector2f& p) const
{
	sf::Vector2f pos = T::getPosition();
	return deg(atan2(-(pos.y-p.y), -(pos.x-p.x)));
}

template <class T> void Entity<T>::moveSec(float vx, float vy)
{
	T::move(vx * getDt(), vy * getDt());
}

template <class T> void Entity<T>::moveSec(const sf::Vector2f& v)
{
	T::move(v.x * getDt(), v.y * getDt());
}

template <class T> void Entity<T>::movePhy()
{
	T::move(speed.x, speed.y);
	speed.x += acceleration.x;
	speed.y += acceleration.y;
}

template <class T> void Entity<T>::movePhySec()
{
	T::move(speed.x * getDt(), speed.y * getDt());
	speed.x += acceleration.x * getDt();
	speed.y += acceleration.y * getDt();
}

template <class T> void Entity<T>::moveToward(float x, float y, float vx, float vy)
{
	sf::Vector2f pos = T::getPosition();
	float distance = getDistance(x, y);
	if(distance)
		moveSec(((x - pos.x) / distance) * vx, ((y - pos.y) / distance) * vy);
}

template <class T> void Entity<T>::moveToward(const sf::Vector2f& p, const sf::Vector2f& v)
{
	sf::Vector2f pos = T::getPosition();
	float distance = getDistance(p.x, p.y);
	if(distance)
		moveSec(((p.x - pos.x) / distance) * v.x, ((p.y - pos.y) / distance) * v.y);
}

template <class T> void Entity<T>::moveTowardInerty(float x, float y, float vx, float vy)
{
	sf::Vector2f pos = T::getPosition();
	moveSec((x - pos.x) * vx, (y - pos.y) * vy);
}

template <class T> void Entity<T>::moveTowardInerty(const sf::Vector2f& p, const sf::Vector2f& v)
{
	sf::Vector2f pos = T::getPosition();
	moveSec((p.x - pos.x) * v.x, (p.y - pos.y) * v.y);
}

template <class T> void Entity<T>::rotateSec(Degre angle)
{
	T::rotate(angle * getDt());
}

template <class T> void Entity<T>::rotateAround(float x, float y, Degre angle)
{
	angle = rad(angle * getDt());
	sf::Vector2f pos = T::getPosition();
	pos.x -= x;
	pos.y -= y;
	T::setPosition(cos(angle) * pos.x - sin(angle) * pos.y,
				   sin(angle) * pos.x + cos(angle) * pos.y);
	pos = T::getPosition();
	T::setPosition(pos.x+x, pos.y+y);
}

template <class T> void Entity<T>::rotateAround(const sf::Vector2f& p, Degre angle)
{
	angle = rad(angle * getDt());
	sf::Vector2f pos = T::getPosition();
	pos.x -= p.x;
	pos.y -= p.y;
	T::setPosition(cos(angle) * pos.x - sin(angle) * pos.y,
				   sin(angle) * pos.x + cos(angle) * pos.y);
	pos = T::getPosition();
	T::setPosition(pos.x+p.x, pos.y+p.y);
}

template <class T> void Entity<T>::rotateAround(float x, float y, Degre angle, float dist)
{
	relativeSpeedRotation += angle * getDt();
	setRotatePosition(x, y , relativeSpeedRotation, dist);
}

template <class T> void Entity<T>::rotateAround(const sf::Vector2f& p, Degre angle, float dist)
{
	relativeSpeedRotation += angle * getDt();
	setRotatePosition(p , relativeSpeedRotation, dist);
}

template <class T> void Entity<T>::rotatePhy()
{
	T::rotate(speedRotation);
	speedRotation += accelerationRotation;
}

template <class T> void Entity<T>::rotatePhySec()
{
	T::rotate(speedRotation * getDt());
	speedRotation += accelerationRotation * getDt();
}

template <class T> bool Entity<T>::collision(float x, float y) const
{
	return T::getGlobalBounds().contains(sf::Vector2f(x, y));
}

template <class T> bool Entity<T>::collision(const sf::Vector2f& p) const
{
	return T::getGlobalBounds().contains(p);
}

template <class T> Entity<T>& Entity<T>::operator=(const Entity<T>& cp)
{
	SystemEntity::operator=(cp);
	T::operator=(cp);
	speed = cp.speed;
	acceleration = cp.acceleration;
	speedRotation = cp.speedRotation;
	accelerationRotation = cp.accelerationRotation;
	relativeSpeedRotation = cp.relativeSpeedRotation;
	return *this;
}

template <class T> Entity<T>& Entity<T>::operator~()
{
	speed = -speed;
	acceleration = -acceleration;
	speedRotation = -speedRotation;
	accelerationRotation = -speedRotation;
	relativeSpeedRotation = -relativeSpeedRotation;
	return *this;
}

template <class U> ostream& operator<<(ostream& out, const Entity<U> &entity)
{
	out << *dynamic_cast<const SystemEntity *>(&entity);
	out << "\n\tspeed: " << entity.speed << "\n\tacceleration: " << entity.acceleration <<
	"\n\tspeed rotation: " << entity.speedRotation <<
	"\n\tacceleration rotation: " << entity.accelerationRotation << "\n\t";
	out << "position: " << entity.getPosition() << "\n\trotation: " << entity.getRotation();
	return out;
}

ostream& operator<<(ostream& out, const sf::Vector2f& v)
{
	return out << "(" << v.x << ", " << v.y << ")";
}

ostream& operator<<(ostream& out, const sf::Vector2i& v)
{
	return out << "(" << v.x << ", " << v.y << ")";
}

template class Entity<sf::RectangleShape>;
template class Entity<sf::CircleShape>;
template class Entity<sf::ConvexShape>;
template class Entity<sf::Text>;
template class Entity<sf::Sprite>;

template ostream& operator<<<sf::RectangleShape>(ostream& out, const Entity<sf::RectangleShape> &entity);
template ostream& operator<<<sf::CircleShape>(ostream& out, const Entity<sf::CircleShape> &entity);
template ostream& operator<<<sf::ConvexShape>(ostream& out, const Entity<sf::ConvexShape> &entity);
template ostream& operator<<<sf::Text>(ostream& out, const Entity<sf::Text> &entity);
template ostream& operator<<<sf::Sprite>(ostream& out, const Entity<sf::Sprite> &entity);


