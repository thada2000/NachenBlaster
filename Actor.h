#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"
#include <list>

using namespace std;
class StudentWorld;

class Actors : public GraphObject {
public:
	Actors(int imageID, double startX, double startY, Direction dir, double size, unsigned int depth, int type);
	virtual int doSomething() = 0;
	virtual bool isDead() = 0;
	virtual ~Actors();
	int getType();
	virtual void collision() = 0;
private:
	int m_type;
	/*each actor is given a type code as follows: NachenBlaster = 0
	                                              star = 1
												  aliens(Smallgon, Smoregon, Snagglegon) = 2
												  cabbage = 3
												  turnip = 4
												  Flatulence Torpedo (player) = 5, (alien)=6
												  */
	                  

};

class NachenBlaster :public Actors {
public:
	NachenBlaster(StudentWorld* world);
	virtual int doSomething();
	int getHealth();
	virtual bool isDead();
	virtual ~NachenBlaster();
	StudentWorld* getWorld();
	virtual void collision();
private:
	StudentWorld* m_world;
	int m_health;
	int m_cabbage;
	int m_torpedoes;
};

class Star :public Actors {
public:
	Star(double width, double height);
	virtual int doSomething();
	virtual bool isDead();
	virtual ~Star();
	virtual void collision();
private:

};

class Cabbage : public Actors {
public:
	Cabbage(NachenBlaster* blast);
	virtual ~Cabbage();
	virtual int doSomething();
	virtual bool isDead();
	virtual void collision();
private:
	bool m_dead;
};

class Turnip : public Actors {
public:

};



class Smoregon : public Actors {
public:
	Smoregon();
	virtual int doSomething();
	virtual bool isDead();
	virtual ~Smoregon();
	int getHealth();
private:
	int m_health;

};

class Smallgon : public Actors {
public:
	Smallgon(StudentWorld* world, NachenBlaster* blaster, list<Actors*> actors);
	virtual int doSomething();
	virtual bool isDead();
	virtual ~Smallgon();
	int getHealth();
private:
	int m_health;
	int m_pathLength;
	int m_speed;
	NachenBlaster* m_blaster;
	list <Actors*> m_acts;
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
