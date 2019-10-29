#ifndef SHADER_HPP
#define SHADER_HPP
#include "Entity.hpp"

namespace se
{
	struct TextureEntity
	{
		Entity *other;
		sf::Image imgCpy;
	};

	class Shader final : public ThreadAble
	{
	private:
		static std::vector<Shader *> threadShaders;
		unsigned radius;
		float basicPower[4] = {0,0,0,1};
		sf::Vector2i lux;
		Entity *luxEntity = nullptr;
		std::vector<TextureEntity> entityList;
		unsigned entityListSize = 0;
		std::string name;
		float luxRgbPower[4] = {1,1,1,1};
		bool fix = true;
	public:
		Shader(std::string name, unsigned radius, float power, sf::Vector2i lux, const sf::Color& luxColor=sf::Color::White);
		Shader(std::string name, unsigned radius, float power, Entity *luxEntity, const sf::Color& luxColor=sf::Color::White);
		~Shader();
		void add(Entity&);
		void update();
		void removeEntity(const Entity&);
		std::string getName();
		Entity *getLuxEntity();
		void setLuxEntity(Entity *, bool=false);
		void setLux(sf::Vector2i);
		void setLuxColor(const sf::Color&);
		void setBasicPower(float r, float g, float b, float a=1.0);
		void setLuxRgbPower(float r, float g, float b, float a=1.0);
		void setRadius(int radius);
		virtual void join(Thread& th) override;
		static Shader *get(std::string name);
		static void flush();
	};
}

#endif
