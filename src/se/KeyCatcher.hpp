#ifndef KEYCATCHER_HPP
#define KEYCATCHER_HPP

namespace se
{
	class KeyCatcher
	{
	public:
		virtual void keyCatch(char keycode) = 0;
	};
}

#endif
