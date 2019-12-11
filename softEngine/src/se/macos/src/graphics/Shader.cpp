#include "Shader.hpp"

using namespace se;

std::vector<Shader *> Shader::threadShaders = std::vector<Shader *>();

Shader::Shader(std::string name, unsigned radius, float power, sf::Vector2i lux, const sf::Color& luxColor) : name(name), radius(radius), lux(lux)
{
	fix = true;
	setLuxColor(luxColor);
	setBasicPower(power, power, power);
	trace("Shader created");
}

Shader::Shader(std::string name, unsigned radius, float power, Entity *lux, const sf::Color& luxColor) : name(name), radius(radius), luxEntity(lux)
{
	fix = false;
	setLuxColor(luxColor);
	setBasicPower(power, power, power);
	trace("Shader created");
}

Shader::~Shader()
{
	for(auto te : entityList)
	{
		te.other->getTexture()->update(te.imgCpy);
	}
	trace("Shader deleted");
}

void Shader::setLuxColor(const sf::Color& c)
{
	luxRgbPower[0] = c.r / 255.0;
	luxRgbPower[1] = c.g / 255.0;
	luxRgbPower[2] = c.b / 255.0;
	luxRgbPower[3] = c.a / 255.0;
}

void Shader::setLuxRgbPower(float r, float g, float b, float a)
{
	luxRgbPower[0] = r;
	luxRgbPower[1] = g;
	luxRgbPower[2] = b;
	luxRgbPower[3] = a;
	for(int i = 0; i < 4; i++)
	{
		basicPower[i] /= luxRgbPower[i] ? luxRgbPower[i] : 1;
	}
}

Shader *Shader::get(std::string name)
{
	for(auto te : Shader::threadShaders)
	{
		if(te->name == name)
		{
			return te;
		}
	}
	return nullptr;
}

void Shader::setRadius(int radius)
{
	this->radius = radius;
}

void Shader::add(Entity& other)
{
	TextureEntity te;
	te.other = &other;
	te.imgCpy = other.getTexture()->copyToImage();
	entityList.push_back(te);
	entityListSize++;
}

void Shader::setLuxEntity(Entity *luxEntity, bool setVisible)
{
	this->luxEntity = luxEntity;
	if(setVisible)
	{
		add(*luxEntity);
	}
}

void Shader::setLux(sf::Vector2i lux)
{
	this->lux = lux;
}

std::string Shader::getName()
{
	return name;
}

void Shader::update()
{
	for(int k = 0; k < entityListSize; k++)
	{
		Entity *e = entityList[k].other;
		e->editTexture([k, e, this](sf::Image& img)
		{
			auto size = img.getSize();
			float memAngle = e->getRotation();
			auto s = e->getSize();
			auto basicPos = e->getTLPosition();
			auto normPos = e->getPosition();
			int newLuxX;
			int newLuxY;
			auto imgFactorSize = sf::Vector2f((s.x / (float)size.x), (s.y / (float)size.y));
			auto pos = fix ? lux : static_cast<sf::Vector2i>(luxEntity->getPosition());
			newLuxX = (pos.x-normPos.x) * cos(radians(-memAngle)) - (pos.y-normPos.y) * sin(radians(-memAngle)) + normPos.x;
			newLuxY = (pos.x-normPos.x) * sin(radians(-memAngle)) + (pos.y-normPos.y) * cos(radians(-memAngle)) + normPos.y;
			for(int i = 0; i < size.x; i++)
			{
				for(int j = 0; j < size.y; j++)
				{
					sf::Color cpyPx = entityList[k].imgCpy.getPixel(i, j);
					if(cpyPx.a == 0) continue;
					int x = (i * imgFactorSize.x + basicPos.x);
					int y = (j * imgFactorSize.y + basicPos.y);
					int distance = util::getDistance(x, y, newLuxX, newLuxY);
					float basicFact = 1 - distance / (float)radius;
					float fact[4];
					for(int f = 0; f < 4; f++)
					{
						fact[f] = basicPower[f] + basicFact;
						if(fact[f] < basicPower[f]) fact[f] = basicPower[f];
						else if(fact[f] > 1) fact[f] = 1;
					}
					unsigned r = (cpyPx.r * fact[0]) * luxRgbPower[0];
					unsigned g = (cpyPx.g * fact[1]) * luxRgbPower[1];
					unsigned b = (cpyPx.b * fact[2]) * luxRgbPower[2];
					unsigned a = (cpyPx.a * fact[3]) * luxRgbPower[3];
					if(r > 255) r = 255;
					if(g > 255) g = 255;
					if(b > 255) b = 255;
					if(a > 255) a = 255;
					img.setPixel(i, j, sf::Color(r,g,b,a));
				}
			}
		});
	}
}

void Shader::setBasicPower(float r, float g, float b, float a)
{
	basicPower[0] = r;
	basicPower[1] = g;
	basicPower[2] = b;
	basicPower[3] = a;
}
/*
fact += ((float)radius / distance);
if(fact > 1) fact = 1; -> avec une source lumineuse plus forte (visuellement)
*/

Entity *Shader::getLuxEntity()
{
	return luxEntity;
}

void Shader::removeEntity(const Entity& other)
{
	for(int i = 0; i < entityListSize; i++)
	{
		if(entityList[i].other == &other)
		{
			entityList[i].other->getTexture()->update(entityList[i].imgCpy);
			entityList.erase(entityList.begin() + i);
			entityListSize--;
			return;
		}
	}
}

/*
if distance < radius then
	fact = 1 - distance / radius
end
*/

void Shader::join(Thread& th)
{
	setThreadRef(th);
	this->setThreadFunctionId(
		th.add([this]()
		{
			this->update();
	}));
	threadShaders.push_back(this);
}

void Shader::flush()
{
	for(auto te : Shader::threadShaders)
	{
		delete te;
	}
	Shader::threadShaders.clear();
}
