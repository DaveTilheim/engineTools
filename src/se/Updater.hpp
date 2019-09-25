#ifndef UPDATER_HPP
#define UPDATER_HPP
#include "debug.hpp"
#define abstract =0

namespace se
{
	class Updater
	{
	protected:
		virtual void update() abstract;
		virtual void render() abstract;
	};
}


#endif
