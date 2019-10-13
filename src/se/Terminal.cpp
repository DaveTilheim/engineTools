#include "Terminal.hpp"

using namespace se;

Terminal::Terminal(int x, int y, int width, int height, sf::Font *font, Application *root)
: Entry(x, y, "> ", font, root, sf::Color::Green)
{
	this->setFillColor(sf::Color::Black);
	this->setNewlineStr("> ");
	this->lockSize();
	this->padding(10);
	this->setSize(sf::Vector2f(width, height));
	this->addCommand("clear", [this](std::vector<std::string>){
		this->setTextWithoutChange("");
		this->cursor = 0;
	});
	this->addCommand("echo", [this](Args args){
		if(args.size() >= 1)
		{
			std::string message = "";
			for(auto s : args)
			{
				message += s+" ";
			}
			message.erase(message.size()-1);
			this->output(message);
		}
	});
	this->addCommand("date", [this](Args args){
		time_t now = time(NULL);
		tm *stm = localtime(&now);
		std::stringstream out;
		out << stm->tm_mday << "/" << stm->tm_mon << "/" << 1900+stm->tm_year << "  " << stm->tm_hour <<":" << stm->tm_min <<":"<<stm->tm_sec;
		this->output(out.str());
	});
	trace("Terminal created");
}

void Terminal::output(std::string out)
{
	this->insert(out+"\n");
}

void Terminal::addCommand(std::string id, std::function<void(std::vector<std::string>)> func)
{
	this->commands[id] = func;
}

void Terminal::runCommand(std::string line, bool rec)
{
	if(not line.size() or not this->commands.size())
	{
		return;
	}
	std::vector<std::string> multcommands = util::split(line, ';');
	std::vector<std::string> command = this->getWords(multcommands[0]);
	multcommands.erase(multcommands.begin());
	if(not rec and this->newlineStr.size())
	{
		command.erase(command.begin());
	}
	std::string idcommand;
	if(command.size() >= 1)
	{
		idcommand = command[0];
		command.erase(command.begin());
	}
	else
	{
		return;
	}
	
	if(this->commands.find(idcommand) != this->commands.end())
	{
		this->commands[idcommand](command);
	}
	else
	{
		this->output("***   '"+idcommand+"'   unknown   ***");
	}
	for(auto s : multcommands)
	{
		util::removeChar(s, ' ');
		this->runCommand(s, true);
	}
}

void Terminal::keyCatch(char kcode)
{
	if(this->focus and kcode)
	{
		if(kcode == '\n' and not this->allowNewline)
		{
			return;
		}
		if(kcode == 8)
		{
			if(not (this->getLastLine() == this->newlineStr))
			{
				this->removeAt(this->cursor);
			}
		}
		else
		{
			trace(std::to_string((int)kcode).c_str());
			this->insert(kcode, this->cursor);
			if(kcode == '\n')
			{
				this->runCommand(this->getLastLine());
				if(this->newlineStr.size())
				{
					this->insert(this->newlineStr, this->cursor);
				}
			}
			if(this->sizeLocked)
			{
				this->outOfBounds();
			}
		}
	}
}
