#ifndef LABELED_PROGRESS_BAR_HPP
#define LABELED_PROGRESS_BAR_HPP
#include "BGProgressBar.hpp"
#include "Label.hpp"

namespace se
{
	class LabeledProgressBar : public BGProgressBar
	{
	protected:
		Label label;
		std::string descr;
		virtual void ajust() override;
	public:
		LabeledProgressBar(float x, float y, float maxSize, float height, Application *root, std::string text, 
			sf::Font *font, double maxVal=100, double val=100);
		Label& getLabel();
		void setDescription(std::string descr);
		virtual void render() override;
	};
}

#endif
