#include "Entity.hpp"


template <class T> Entity<T>::Entity() : SystemEntity(), T()
{
	trace("entity creation");
}

template <class T> Entity<T>::Entity(const Entity<T>& cp) : SystemEntity(cp), T(cp)
{
	trace("entity creation");
}

template <class T> Entity<T>::~Entity()
{
	trace("entity destruction");
}

template <class T> Entity<T>& Entity<T>::operator=(const Entity<T>& cp)
{
	SystemEntity::operator=(cp);
	T::operator=(cp);
	return *this;
}

template <class T> void Entity<T>::view(sf::RenderWindow& window) const
{
	window.draw(*this);
}

template <class T> void Entity<T>::setRotatePosition(const sf::Vector2f& ref, float angle, float distance)
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

template <class T> void Entity<T>::setAcceleration(float ax, float ay)
{
	acceleration.x = ax;
	acceleration.y = ay;
}

template <class T> sf::Vector2f Entity<T>::getSpeed() const
{
	return speed;
}

template <class T> sf::Vector2f Entity<T>::getAcceleration() const
{
	return acceleration;
}

template <class T> void Entity<T>::moveSec(float vx, float vy)
{
	T::move(vx * getDt(), vy * getDt());
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

template <class U> ostream& operator<<(ostream& out, const Entity<U> &entity)
{
	return out << *dynamic_cast<const SystemEntity *>(&entity);
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


