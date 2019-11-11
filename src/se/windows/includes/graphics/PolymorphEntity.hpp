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
		std::function<void(T*)> deleteLambda = [](T*){};
	public:
		using T::T;
		virtual ~PolymorphEntity<T>();
		PolymorphEntity<T>(const PolymorphEntity<T>&other);
		void setUpdate(std::function<void(T*)> updateLambda);
		void setDelete(std::function<void(T*)> deleteLambda);
		virtual void update() override;
	};

	template <class T> PolymorphEntity<T>::~PolymorphEntity()
	{
		this->deleteLambda(this);
		trace("PolymorphEntity deleted");
	}

	template <class T> void PolymorphEntity<T>::setDelete(std::function<void(T*)> deleteLambda)
	{
		this->deleteLambda = deleteLambda;
	}

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
