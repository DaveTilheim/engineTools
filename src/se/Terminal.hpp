#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "Entry.hpp"
#include <ctime>

namespace se
{
	typedef std::vector<std::string> Args;
	class Terminal : public Entry
	{
	private:
		std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
		void runCommand(std::string line, bool rec=false);
	public:
		Terminal(int x, int y, int width, int height, sf::Font *font, Application *root);
		void addCommand(std::string, std::function<void(std::vector<std::string>)>);
		void output(std::string out);
		virtual void keyCatch(char keycode) override;
	};
}

#endif
