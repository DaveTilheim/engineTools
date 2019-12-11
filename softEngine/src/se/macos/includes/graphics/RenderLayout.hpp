#ifndef RENDER_LAYOUT_HPP
#define RENDER_LAYOUT_HPP
#include "Entity.hpp"

namespace se
{
	class RenderLayout
	{
	private:
		static RenderLayout *defaultLayout;
		static std::vector<RenderLayout *> layouts;
		static unsigned layoutsSize;
		static bool compare(RenderLayout *l1, RenderLayout *l2);
		std::string name;
		unsigned order = -1;
		std::vector<Entity *> entityList;
		unsigned entityListSize = 0;
	public:
		RenderLayout(std::string name, unsigned order=-1);
		virtual ~RenderLayout();
		unsigned getNbEntity();
		Entity *getEntity(unsigned i);
		void addEntity(Entity *e);
		static void addInLayout(std::string name, Entity *e);
		static void flush();
		static unsigned getSize();
		static RenderLayout *getLayout(unsigned i);
		static RenderLayout *getLayout(std::string name);
		static void removeEntity(Entity *e);
		static void swapLayout(std::string l1, std::string l2);
		static void changeLayout(std::string l, Entity *e);
	};
}

#endif
