#ifndef LAMBDADYNAMIC_HPP
#define LAMBDADYNAMIC_HPP
#include <functional>
#include <type_traits>
#include "Dynamic.hpp"
#include "Entity.hpp"
#include "RectEntity.hpp"
#include "CircleEntity.hpp"
#define Lambda LambdaDynamic

using namespace std;

template <class T> class LambdaDynamic final : public T
{
private:
	function<void(T&)> updateLambda = [](T&){};
protected:
	void update() override;
public:
	using T::T;
	LambdaDynamic(const LambdaDynamic<T>& cp);
	void setUpdate(function<void(T&)>);
	LambdaDynamic<T>& operator=(const LambdaDynamic<T>& cp);
};

typedef LambdaDynamic<Dynamic> LDynamic;
typedef LambdaDynamic<Entity<sf::RectangleShape>> LEntityRectangleShape;
typedef LambdaDynamic<Entity<sf::CircleShape>> LEntityCircleShape;
typedef LambdaDynamic<Entity<sf::ConvexShape>> LEntityConvexShape;
typedef LambdaDynamic<Entity<sf::Text>> LEntityText;
typedef LambdaDynamic<Entity<sf::Sprite>> LEntitySprite;
typedef LambdaDynamic<RectEntity> LRectEntity;
typedef LambdaDynamic<CircleEntity> LCircleEntity;

#endif
