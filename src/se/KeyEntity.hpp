#ifndef KEY_ENTITY_HPP
#define KEY_ENTITY_HPP
#include "Utilities.hpp"
#include <vector>
#include <functional>

namespace se
{
	template <class T> struct KeyLambda
	{
		std::function<void(T *)> lambda;
		sf::Keyboard::Key key;
		bool active = true;
		bool released = true;
	};

	template <class T> class KeyEntity : public T
	{
	protected:
		std::map<sf::Keyboard::Key, KeyLambda<T>> keyLambdas;
		void keyManager();
	public:
		using T::T;
		virtual void update() override;
		void setKey(sf::Keyboard::Key key, std::function<void(T *)> lambda, bool=false,std::function<void(T *)> =[](T *){});
		void keyState(sf::Keyboard::Key,bool state);
		void removeKey(sf::Keyboard::Key);
		bool& operator[](sf::Keyboard::Key);
	};

	template <class T> void KeyEntity<T>::update()
	{
		if(!std::is_abstract<T>())
		{
			this->T::update();
		}
		this->keyManager();
	}

	template <class T> void KeyEntity<T>::keyManager()
	{
		for(auto l : this->keyLambdas)
		{
			if(l.second.active)
			{
				l.second.lambda(this);
			}
		}
	}

	template <class T> void KeyEntity<T>::setKey(sf::Keyboard::Key key, std::function<void(T *)> lambda, bool oneshot, std::function<void(T *)> releaseLambda)
	{
		this->keyLambdas[key] = KeyLambda<T>();
		this->keyLambdas[key].key = key;
		if(not oneshot)
		{
			this->keyLambdas[key].lambda = [key, lambda](T *e){
				if(util::isKeyPressed(key))
				{
					lambda(e);
				}
			};
		}
		else
		{
			this->keyLambdas[key].lambda = [this, key, lambda, releaseLambda](T *e){
				if(util::isKeyPressed(this->keyLambdas[key].key))
				{
					if(this->keyLambdas[key].released)
					{
						lambda(e);
						this->keyLambdas[key].released = false;
					}
				}
				else
				{
					if(not this->keyLambdas[key].released)
					{
						releaseLambda(e);
					}
					this->keyLambdas[key].released = true;
				}
			};
		}
	}

	template <class T> void KeyEntity<T>::keyState(sf::Keyboard::Key key, bool state)
	{
		this->keyLambdas[key].active = state;
	}

	template <class T> void KeyEntity<T>::removeKey(sf::Keyboard::Key key)
	{
		this->keyLambdas.erase(key);
	}

	template <class T> bool& KeyEntity<T>::operator[](sf::Keyboard::Key key)
	{
		return this->keyLambdas[key].active;
	}
}

#endif
