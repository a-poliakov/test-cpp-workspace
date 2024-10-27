#include <iostream>
#include <list>
#include "EventManager.h"
#include "IMovable.h"
#include "IRotable.h"

const int Xmax = 100;
const int Ymax = 100;
const int Tmax = 100;
const int dt = 1;

class IMovable;
class IRotable;

class EventManagerP
{
public:
    objectList* std::list<object>;
    int countX, countY;

    EventManagerP():
        countX(0),
        countY(0)
    {
    }
    ~EventManagerP()
    {
    }
    bool init(objectList* starship)
    {
        int count = starship->count();
        for(int i = 0; i < count; i ++)
        {
            const object *obj = starship->list().at(i);
            if(!checkPlaceObject(obj)) return false;
            if(!checkVelocityObject(obj)) return false;
            list = starship;
        }
        return true;
    }
    bool checkPlaceObject(const object *obj)
    {
        if(obj->placeX() < 0 || obj->placeY() < 0)
            return false;
        return true;
    }
    bool checkVelocityObject(const object *obj)
    {
        if(obj->velocity() < 0 || obj->angular() < 0)
            return false;
        return true;
    }
    bool execute(objectList* starship)
    {
        std::cout << "Start moving objects" << std::endl;
        int count = starship->count();
        for(int i = 0; i < count; i ++)
        {
            object *obj = starship->list().at(i);
            if(obj->velocity() != 0)
            {
                IMovable *mov = new IMovable(obj->placeX(), obj->placeY(),
                                             obj->velocity(), obj->angular(), dt);
                mov->getPosition(obj, dt);
            }
            if(obj->angular() != 0)
            {
                IRotable *rot = new IRotable(obj->placeX(), obj->placeY(),
                                             obj->angular());
                rot->getAngular(obj, 15);
            }
        }
        return true;
    }
};

EventManager::EventManager() : imp(new EventManagerP)
{
}

EventManager::~EventManager()
{
    delete imp;
}

bool EventManager::init(objectList* list)
{
    bool result = imp->init(list);
    return result;
}

bool EventManager::execute(objectList* list)
{
    bool result = imp->execute(list);
    return result;
}
