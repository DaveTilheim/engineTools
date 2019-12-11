#ifndef LINKED_ENTITY_HPP
#define LINKED_ENTITY_HPP
#include "RectEntity.hpp"
#include "CircleEntity.hpp"
#include <type_traits>

namespace se
{
	struct Linked
	{
		Entity *linked = nullptr;
		bool tomanage = false;
		bool todelete = false;
		Linked(Entity&, bool,bool);
		~Linked();
	};

	template <class T> class LinkedEntity : public T
	{
	protected:
		std::map<std::string, Linked *> linkedList;
	public:
		using T::T;
		virtual ~LinkedEntity();
		virtual void update() override;
		virtual void render() override;
		virtual void setPosition(float x, float y) override;
		virtual void setTLPosition(float x, float y) override;
		virtual void setRotation(float angle) override;
		virtual void rotate(float angle) override;
		virtual void move(float x, float y) override;
		virtual void setScale(float sx, float sy) override;
		void link(std::string id, Entity&, bool=false, bool=false);
		Entity *getLinked(std::string id);
	};

	template <class T> Entity *LinkedEntity<T>::getLinked(std::string id)
	{
		return linkedList[id]->linked;
	}

	template <class T> void LinkedEntity<T>::setScale(float sx, float sy)
	{
		this->T::setScale(sx, sy);
		for(auto it : linkedList)
		{
			it.second->linked->setScale(sx, sy);
		}
	}

	template <class T> void LinkedEntity<T>::move(float x, float y)
	{
		this->T::move(x, y);
		for(auto it : linkedList)
		{
			it.second->linked->move(x, y);
		}
	}

	template <class T> void LinkedEntity<T>::rotate(float angle)
	{
		auto pos = this->getPosition();
		this->T::rotate(angle);
		for(auto it : linkedList)
		{
			it.second->linked->rotate(angle);
			it.second->linked->rotate(angle, pos.x, pos.y);
		}
	}

	template <class T> void LinkedEntity<T>::setRotation(float angle)
	{
		float newAngle = angle - this->getRotation();
		this->T::setRotation(angle);
		auto pos = this->getPosition();
		for(auto it : linkedList)
		{
			it.second->linked->rotation(newAngle, pos.x, pos.y);
			it.second->linked->rotation(newAngle);
		}
	}

	template <class T> void LinkedEntity<T>::setTLPosition(float x, float y)
	{
		sf::Vector2f pos = this->T::getTLPosition();
		this->T::setTLPosition(x, y);
		float mvx = x - pos.x;
		float mvy = y - pos.y;
		for(auto it : linkedList)
		{
			auto lpos = it.second->linked->getTLPosition();
			it.second->linked->setTLPosition(lpos.x + mvx, lpos.y + mvy);
		}
	}

	template <class T> void LinkedEntity<T>::setPosition(float x, float y)
	{
		sf::Vector2f pos = this->T::getPosition();
		this->T::setPosition(x, y);
		float mvx = x - pos.x;
		float mvy = y - pos.y;
		for(auto it : linkedList)
		{
			auto lpos = it.second->linked->getPosition();
			it.second->linked->setPosition(lpos.x + mvx, lpos.y + mvy);
		}
	}

	template <class T> LinkedEntity<T>::~LinkedEntity()
	{
		for(auto it : linkedList)
		{
			delete it.second;
		}
	}

	template <class T> void LinkedEntity<T>::update()
	{
		if(!std::is_abstract<T>())
		{
			this->T::update();
		}
		for(auto it : linkedList)
		{
			if(it.second->tomanage)
			{
				if(it.second->linked->getUpdateState())
				{
					it.second->linked->updateIfActivate();
				}
			}
		}
	}

	template <class T> void LinkedEntity<T>::render()
	{
		this->T::render();
		for(auto it : linkedList)
		{
			if(it.second->tomanage)
			{
				if(it.second->linked->getRenderState())
				{
					it.second->linked->renderIfActivate();
				}
			}
		}
	}

	template <class T> void LinkedEntity<T>::link(std::string id, Entity& le, bool tomanage, bool todelete)
	{
		if(linkedList.find(id) != linkedList.end())
		{
			delete linkedList[id];
		}
		linkedList[id] = new Linked(le, tomanage, todelete);
	}
}

#endif
