#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "SystemEntity.hpp"
#include "Debug.hpp"
#include "Utils.hpp"
#include "GlobalInfo.hpp"
#include <SFML/Graphics.hpp>

enum Origin
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT
};

template <class T> class Entity : public SystemEntity, public T
{
private:
	sf::Vector2f speed;
	sf::Vector2f acceleration;
protected:
	virtual void update() override = 0;
	virtual void view(sf::RenderWindow& window) const override;
public:
	Entity();
	Entity(const Entity<T>& cp);
	virtual ~Entity();
	void setRotatePosition(const sf::Vector2f& ref, float angle, float distance);
	void setSideOrigin(Origin origin=MIDDLE_CENTER);
	void setSpeed(float vx, float vy);
	void setAcceleration(float ax, float ay);
	sf::Vector2f getSpeed() const;
	sf::Vector2f getAcceleration() const;
	void moveSec(float vx, float vy);
	void movePhy();
	void movePhySec();
	Entity<T>& operator=(const Entity<T>& cp);
	template <class U> friend ostream& operator<<(ostream& out, const Entity<U> &entity);
};


#endif
