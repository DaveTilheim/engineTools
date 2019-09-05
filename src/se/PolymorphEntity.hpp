#ifndef __POLYMORPH_ENTITY_HPP__
#define __POLYMORPH_ENTITY_HPP__
#include "RectEntity.hpp"
#include "CircleEntity.hpp"
#include <functional>

namespace se
{
	template <class T=RectEntity>
	class PolymorphEntity : public T
	{
	private:
		std::function<void()> updateLambda;
	public:
		using T::T;
		void setUpdate(std::function<void()> updateLambda);
		virtual void update() override;
	};
	template <class T>
	void PolymorphEntity<T>::setUpdate(std::function<void()> updateLambda)
	{
		this->updateLambda = updateLambda;
	}

	template <class T>
	void PolymorphEntity<T>::update()
	{
		this->updateLambda();
	}

}

#endif
