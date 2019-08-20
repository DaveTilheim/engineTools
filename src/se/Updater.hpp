#ifndef __UPDATER_HPP__
#define __UPDATER_HPP__

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
