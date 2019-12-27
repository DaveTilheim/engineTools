#ifndef SMARTAPPLICATION_HPP
#define SMARTAPPLICATION_HPP
#include "Application.hpp"
#include "Entity.hpp"
#include "Timer.hpp"
#include <vector>
#include <sstream>
#include <map>

#define infer_type_mecanism

enum SmartTrait
{
	NONE = 		0x0000,
	DELETABLE = 0x0001
};

SmartTrait operator|(SmartTrait s1, SmartTrait s2);

struct SmartObject
{
	SmartTrait traits;
	Dynamic *object;
	SmartObject(Dynamic *object, SmartTrait trait=NONE) : traits(trait), object(object) {}
	bool deletable() const {return traits & DELETABLE;}
};


class SmartApplication : public Application
{
private:
	vector<SmartObject> entities;
	vector<SmartObject> subApplications;
	vector<SmartObject> timers;
	vector<Dynamic*> removeLaterList;
	vector<SmartObject> addLaterList;
	map<string, sf::Texture *> textures;
	bool toRemove = false;
	bool toAdd = false;
	void updateEntities();
	void updateRemoving();
	void updateAdding();
	void updateSubApplications();
	void updateTimers();
	void drawEntities(sf::RenderWindow& win) const;
	void infer_type_mecanism remove(Dynamic *obj); // remove an object from the application
	void removeEntity(SystemEntity* entity); // remove a SystemEntity from the application
	void removeSubApplication(Application* subApp); // remove a SubApplication from the application
	void removeTimer(Timer *timer);
	void infer_type_mecanism add(SmartObject&); // add a smart object to the application
	void flushEntities();
	void flushSubApplications();
	void flushTextures();
	void flushTimers();
	void flush();
protected:
	SmartApplication& app;
	virtual void update() override;
	virtual void view(sf::RenderWindow& win) const override;
	virtual void load() override = 0;
	void infer_type_mecanism add(Dynamic& obj, SmartTrait traits=NONE); // add an object to the application
	void infer_type_mecanism add(Dynamic* obj, SmartTrait traits=NONE); // add an object to the application
	void addEntity(SystemEntity& entity, SmartTrait traits=NONE); // add a SystemEntity to the application
	void addEntity(SystemEntity* entity, SmartTrait traits=NONE); // add a SystemEntity to the application
	void addSubApplication(Application& subApp, SmartTrait traits=NONE); // add a SubApplication to the application
	void addSubApplication(Application* subApp, SmartTrait traits=NONE); // add a SubApplication to the application
	void addTimer(Timer& subApp, SmartTrait traits=NONE); // add a Timer to the application
	void addTimer(Timer* subApp, SmartTrait traits=NONE); // add a Timer to the application
	void addLater(Dynamic& entity, SmartTrait traits=NONE); // add an object from the application at the beggining of the next frame
	void addLater(Dynamic* entity, SmartTrait traits=NONE); // add an object from the application at the beggining of the next frame
	void addTexture(string filename);
	void infer_type_mecanism removeLater(Dynamic& entity); // remove an object from the application at the end of the current frame
	void infer_type_mecanism removeLater(Dynamic* entity); // remove an object from the application at the end of the current frame
	void removeTexture(string textureName);
	void removeTexture(sf::Texture *textureName);
	void removeTexture(SystemEntity *entity);
	sf::Texture* getTexture(string textureName);
	sf::Texture* duplicateTexture(string textureName, string otherName);
	sf::Texture* duplicateTexture(string textureName, SystemEntity* entity);
	sf::Texture* duplicateTexture(string textureName, SystemEntity& entity);
public:
	SmartApplication(string title="SmartApplication");
	SmartApplication(int width, int height, string title="SmartApplication");
	virtual ~SmartApplication();
	int countEntities() const;
	int countSubApplications() const;
	SmartApplication& infer_type_mecanism operator<<(Dynamic& obj); // add an object to the application with No SmartTrait (begin next frame)
	SmartApplication& infer_type_mecanism operator<<(Dynamic* obj); // add an object to the application with DELETABLE SmartTrait (begin next frame)
	SmartApplication& infer_type_mecanism operator>>(Dynamic& obj); // add an object to the application with No SmartTrait (current frame)
	SmartApplication& infer_type_mecanism operator>>(Dynamic* obj); // add an object to the application with DELETABLE SmartTrait (current frame)
	SmartApplication& operator<<(string txtr);
	sf::Texture *operator[](string textureName);
};



#endif
