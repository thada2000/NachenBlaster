#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include<list>
#include "Actor.h"
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	virtual int init();
	virtual int move();
	virtual void cleanUp();

private:
	NachenBlaster* m_nachy;
	list<Actors*> m_actors;
	int m_eDefeated;
	list<Actors*> ::iterator m_it;
};

#endif // STUDENTWORLD_H_
