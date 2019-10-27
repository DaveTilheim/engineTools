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
		float power = 0.0;
		sf::Vector2i lux;
		Entity *luxEntity = nullptr;
		std::vector<TextureEntity> entityList;
		unsigned entityListSize = 0;
		std::string name;
		bool fix = true;
	public:
		Shader(std::string name, unsigned radius, float power, sf::Vector2i lux);
		Shader(std::string name, unsigned radius, float power, Entity *luxEntity);
		~Shader();
		void add(Entity&);
		void update();
		void removeEntity(const Entity&);
		std::string getName();
		Entity *getLuxEntity();
		void setLuxEntity(Entity *);
		void setLux(sf::Vector2i);
		virtual void join(Thread& th) override;
		static void flush();
	};
}

#endif
