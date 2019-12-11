#ifndef UPDATER_HPP
#define UPDATER_HPP
#include "debug.hpp"
#define abstract =0

namespace se
{
	class Updater
	{
	private:
		bool updateState = true;
		bool renderState = true;
	protected:
		virtual void update() abstract;
		virtual void render() abstract;
	public:
		virtual void updateIfActivate() final;
		virtual void renderIfActivate() final;
		virtual void activateUpdate() final;
		virtual void disactivateUpdate() final;
		virtual void activateRender() final;
		virtual void disactivateRender() final;
		virtual bool getUpdateState() final;
		virtual bool getRenderState() final;
		virtual unsigned char getStatus() final;
		virtual void pause() final;
		virtual void play() final;
	};
}


#endif
