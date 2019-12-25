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
	sf::Vector2f speed = sf::Vector2f(0,0);
	sf::Vector2f acceleration = sf::Vector2f(0,0);
	Degre speedRotation = 0.0;
	Degre accelerationRotation = 0.0;
	Degre relativeSpeedRotation = 0.0;
protected:
	virtual void update() override = 0;
	virtual void view(sf::RenderWindow& window) const override;
public:
	Entity();
	Entity(float x, float y);
	Entity(const sf::Vector2f& pos);
	Entity(const Entity<T>& cp);
	virtual ~Entity();
	void setRotatePosition(float x, float y, Degre angle, float distance);
	void setRotatePosition(const sf::Vector2f& ref, Degre angle, float distance);
	void setSideOrigin(Origin origin=MIDDLE_CENTER);
	void setSpeed(float vx, float vy);
	void setSpeed(const sf::Vector2f& v);
	void setAcceleration(float ax, float ay);
	void setAcceleration(const sf::Vector2f& a);
	void setSpeedRotation(Degre vr);
	void setAccelerationRotation(Degre ar);
	void setRelativeRotation(float x, float y);
	void setRelativeRotation(const sf::Vector2f& p);
	sf::Vector2f getSidePosition(Origin origin=MIDDLE_CENTER) const;
	sf::Vector2f getSpeed() const;
	sf::Vector2f getAcceleration() const;
	Degre getSpeedRotation() const;
	Degre getAccelerationRotation() const;
	sf::Vector2f getComponent(float x, float y, float v) const;
	sf::Vector2f getComponent(const sf::Vector2f& p, float v) const;
	float getDistance(float x, float y) const;
	float getDistance(const sf::Vector2f& p) const;
	Degre getRelativeRotation(float x, float y) const;
	Degre getRelativeRotation(const sf::Vector2f& p) const;
	void moveSec(float vx, float vy);
	void moveSec(const sf::Vector2f& v);
	void movePhy();
	void movePhySec();
	void moveToward(float x, float y, float vx, float vy);
	void moveToward(const sf::Vector2f& p, const sf::Vector2f& v);
	void moveTowardInerty(float x, float y, float vx, float vy);
	void moveTowardInerty(const sf::Vector2f& p, const sf::Vector2f& v);
	void rotateSec(Degre angle);
	void rotateAround(float x, float y, Degre vangle);
	void rotateAround(const sf::Vector2f& p, Degre vangle);
	void rotateAround(float x, float y, Degre vangle, float dist);
	void rotateAround(const sf::Vector2f& p, Degre vangle, float dist);
	void rotatePhy();
	void rotatePhySec();
	bool collision(float x, float y) const;
	bool collision(const sf::Vector2f& p) const;
	bool collision(const sf::Rect<float>& other) const;
	Entity<T>& operator=(const Entity<T>& cp);
	Entity<T>& operator~();
	operator sf::Rect<float>();
	template <class U> friend ostream& operator<<(ostream& out, const Entity<U> &entity);
};

ostream& operator<<(ostream& out, const sf::Vector2f& v);
ostream& operator<<(ostream& out, const sf::Vector2i& v);


#endif
