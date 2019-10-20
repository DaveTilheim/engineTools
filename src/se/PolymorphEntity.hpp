#ifndef POLYMORPH_ENTITY_HPP
#define POLYMORPH_ENTITY_HPP
#include "Widget.hpp"
#include <functional>
#include <type_traits>
#define Poly PolymorphEntity

namespace se
{
	template <class T=RectEntity>
	class PolymorphEntity : public T
	{
	private:
		std::function<void(T*)> updateLambda = [](T*){};
	public:
		using T::T;
		PolymorphEntity<T>(const PolymorphEntity<T>&other);
		void setUpdate(std::function<void(T*)> updateLambda);
		virtual void update() override;
	};

	template <class T>
	PolymorphEntity<T>::PolymorphEntity(const PolymorphEntity<T>&other) : T(other)
	{
		this->setUpdate(other.updateLambda);
		trace("PolymorphEntity created");
	}

	template <class T>
	void PolymorphEntity<T>::setUpdate(std::function<void(T*)> updateLambda)
	{
		this->updateLambda = updateLambda;
	}

	template <class T>
	void PolymorphEntity<T>::update()
	{
		if(!std::is_abstract<T>())
		{
			this->T::update();
		}
		this->updateLambda(dynamic_cast<T *>(this));
	}
}

#endif
