#ifndef UPDATER_HPP
#define UPDATER_HPP

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
