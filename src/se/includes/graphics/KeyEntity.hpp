#ifndef KEY_ENTITY_HPP
#define KEY_ENTITY_HPP
#include "Utilities.hpp"
#include "debug.hpp"
#include <vector>
#include <functional>

namespace se
{
	template <class T> struct KeyLambda
	{
		std::function<void(T *)> unpackedLambda;
		std::function<void(T *)> releaseLambda;
		std::function<void(T *)> lambda;
		sf::Keyboard::Key key;
		bool active = true;
		bool released = true;
		bool oneshot = false;
	};
	
	template <class T> class KeyEntity : public T
	{
	protected:
		std::map<sf::Keyboard::Key, KeyLambda<T>> keyLambdas;
		void keyManager();
	public:
		using T::T;
		KeyEntity(const KeyEntity<T>&);
		virtual void update() override;
		void setKey(sf::Keyboard::Key key, std::function<void(T *)> lambda, bool=false,std::function<void(T *)> =[](T *){});
		void keyState(sf::Keyboard::Key,bool state);
		void removeKey(sf::Keyboard::Key);
		bool& operator[](sf::Keyboard::Key);
	};

	template <class T> KeyEntity<T>::KeyEntity(const KeyEntity<T>& cp) : T(cp)
	{
		for(auto kl : cp.keyLambdas)
		{
			this->setKey(kl.second.key, kl.second.unpackedLambda, kl.second.oneshot, kl.second.releaseLambda);
		}
		trace("KeyEntity created");
	}

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
		this->keyLambdas[key].unpackedLambda = lambda;
		this->keyLambdas[key].releaseLambda = releaseLambda;
		this->keyLambdas[key].oneshot = oneshot;
		this->keyLambdas[key].key = key;
		if(not oneshot)
		{
			this->keyLambdas[key].lambda = [this,key, lambda, releaseLambda](T *e){
				if(util::isKeyPressed(key))
				{
					this->keyLambdas[key].released = false;
					lambda(e);
				}
				else
				{
					if(not this->keyLambdas[key].released)
					{
						this->keyLambdas[key].released = true;
						releaseLambda(e);
					}
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
