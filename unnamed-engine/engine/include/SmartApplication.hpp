#ifndef SMARTAPPLICATION_HPP
#define SMARTAPPLICATION_HPP
#include "Application.hpp"
#include "SystemEntity.hpp"
#include <vector>

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
	vector<Dynamic*> removeLaterList;
	vector<SmartObject> addLaterList;
	bool toRemove = false;
	bool toAdd = false;
	void updateEntities();
	void updateRemoving();
	void updateAdding();
	void updateSubApplications();
	void drawEntities(sf::RenderWindow& win) const;
	void infer_type_mecanism remove(Dynamic *obj); // remove an object from the application
	void removeEntity(SystemEntity* entity); // remove a SystemEntity from the application
	void removeSubApplication(Application* subApp); // remove a SubApplication from the application
	void infer_type_mecanism add(SmartObject&); // add a smart object to the application
	void flushEntities();
	void flushSubApplications();
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
	void infer_type_mecanism removeLater(Dynamic& entity); // remove an object from the application at the end of the current frame
	void infer_type_mecanism removeLater(Dynamic* entity); // remove an object from the application at the end of the current frame
	void addLater(Dynamic& entity, SmartTrait traits=NONE); // add an object from the application at the beggining of the next frame
	void addLater(Dynamic* entity, SmartTrait traits=NONE); // add an object from the application at the beggining of the next frame
public:
	SmartApplication(string title="SmartApplication");
	SmartApplication(int width, int height, string title="SmartApplication");
	virtual ~SmartApplication();
	SmartApplication& infer_type_mecanism operator<<(Dynamic& obj); // add an object to the application with No SmartTrait
	SmartApplication& infer_type_mecanism operator<<(Dynamic* obj); // add an object to the application with DELETABLE SmartTrait
};

#endif
