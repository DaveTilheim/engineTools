#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP


class Dynamic
{
private:
	bool dynamicState;
protected:
	virtual void update() = 0;
public:
	Dynamic(bool state=true);
	Dynamic(const Dynamic& cp);
	bool getDynamicState() const;
	void setDynamicState(bool state);
	void _update();
	Dynamic& operator=(const Dynamic& cp);
};

#endif
