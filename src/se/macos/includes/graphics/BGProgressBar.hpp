#ifndef BGPROGRESS_BAR_HPP
#define BGPROGRESS_BAR_HPP
#include "ProgressBar.hpp"

namespace se
{
	class BGProgressBar : public ProgressBar
	{
	protected:
		sf::Color bgColorPG = sf::Color::Black;
	public:
		using ProgressBar::ProgressBar;
		virtual void render() override;
		void setBgColor(const sf::Color &color);
	};
}

#endif
