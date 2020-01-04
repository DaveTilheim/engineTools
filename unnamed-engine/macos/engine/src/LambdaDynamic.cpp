#include "LambdaDynamic.hpp"


template <class T> LambdaDynamic<T>::LambdaDynamic(const LambdaDynamic<T>& cp) : T(cp), updateLambda(cp.updateLambda)
{

}

template <class T> void LambdaDynamic<T>::update()
{
	updateLambda(*this);
}

template <class T> void LambdaDynamic<T>::setUpdate(function<void(T&)> f)
{
	updateLambda = f;
}

template <class T> LambdaDynamic<T>& LambdaDynamic<T>::operator=(const LambdaDynamic<T>& cp)
{
	T::operator=(cp);
	updateLambda = cp.updateLambda;
	return *this;
}

template class LambdaDynamic<Dynamic>;
template class LambdaDynamic<Entity<sf::RectangleShape>>;
template class LambdaDynamic<Entity<sf::CircleShape>>;
template class LambdaDynamic<Entity<sf::ConvexShape>>;
template class LambdaDynamic<Entity<sf::Sprite>>;
template class LambdaDynamic<Entity<sf::Text>>;
template class LambdaDynamic<RectEntity>;
template class LambdaDynamic<CircleEntity>;
template class LambdaDynamic<ConvexEntity>;
template class LambdaDynamic<SpriteEntity>;
template class LambdaDynamic<TextEntity>;
template class LambdaDynamic<ProgressBar>;
template class LambdaDynamic<TextProgressBar>;
template class LambdaDynamic<InputEntity>;
