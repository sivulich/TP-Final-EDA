#pragma once
#include "../../Graphics/src/Observers/observer.h"
#include <list>

class BaseModel
{
public:
	void attach(Observer* o) { observers.push_back(o); }
	void detach(Observer* o) { observers.remove(o); } 

protected:
	void notify()
	{
		for(auto& obs : observers)
			obs->update();
	}

private:
	std::list<Observer*> observers;
};

