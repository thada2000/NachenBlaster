#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <cmath>
Actors::Actors(int imageID, double startX, double startY, Direction dir, double size, unsigned int depth, int type) : GraphObject(imageID, startX, startY, dir, size, depth) { m_type = type; }

Actors::~Actors() {
}

int Actors::getType() { return m_type; }

Star::Star(double width, double height) : Actors(IID_STAR, width, height, 0, randInt(5, 50) / 100.0, 3, 1) {}



int Star::doSomething() {
	moveTo(getX() - 1, getY());
	return 0;
}

bool Star::isDead() {
	if (getX() < 0 || getY() < 0)
		return true;
	return false;
}

void Star::collision() {}
Star::~Star() {}

NachenBlaster::NachenBlaster(StudentWorld* world) :Actors(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0,0) {
	m_world = world;
	m_cabbage = 50;
	m_torpedoes = 0;
}
void NachenBlaster::collision() { m_health -= 5; }
NachenBlaster::~NachenBlaster(){}
bool NachenBlaster::isDead() { return(m_health <= 0); }
int NachenBlaster::getHealth() { return m_health; }
StudentWorld* NachenBlaster::getWorld() { return m_world; }
int NachenBlaster::doSomething() {
	int ch;
	if (getWorld()->getKey(ch)) {
		switch (ch) {
		case KEY_PRESS_DOWN:
			if (getY() >0 )
				moveTo(getX(), getY() - 6);
			m_cabbage += 1;
			return 0;
			break;
		case KEY_PRESS_UP:
			if (getY() <VIEW_HEIGHT - 1)
				moveTo(getX(), getY() +6);
			m_cabbage += 1;
			return 0;
			break;
		case KEY_PRESS_LEFT:
			if (getX() >0)
				moveTo(getX()-6, getY());
			m_cabbage += 1;
			return 0;
			break;
		case KEY_PRESS_RIGHT:
			if (getX() < VIEW_WIDTH - 1)
				moveTo(getX() + 6, getY());
			m_cabbage += 1;
			return 0;
			break;
		case KEY_PRESS_SPACE:
			if (m_cabbage >= 5)
				m_cabbage -= 5;
			m_cabbage += 1;
			m_world->playSound(SOUND_PLAYER_SHOOT);
			return 1;
			break;
		}
	}
	return -1;
			
	

 }
void Cabbage::collision() { m_dead = true; }
bool Cabbage::isDead() { return(m_dead || getX() > VIEW_WIDTH - 1); }
Cabbage::Cabbage(NachenBlaster* blast):Actors(IID_CABBAGE, blast->getX()+6, blast->getY(),0, 0.5, 1,3) {
	m_dead = false;
}
Cabbage::~Cabbage(){}
int Cabbage::doSomething() {
	if (getX() < VIEW_WIDTH - 1) {
		moveTo(getX() + 8, getY());
		setDirection(getDirection() + 20);
	}
	return 0;
}

Smallgon::Smallgon(StudentWorld* world, NachenBlaster* blaster, list<Actors*> actors) :Actors(IID_SMALLGON, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1), 0, 1.5, 1,2) {
	m_health = 5 * ((world->getLevel() + 1)*0.1);
	m_speed = 2;
	m_pathLength = 0;
	m_blaster = blaster;
	m_acts = actors;
}

int Smallgon::doSomething() {
	if (m_health <= 0)
		return 0;
	double x = sqrt(pow(getX() + m_blaster->getX(),2.0) + pow(getX() + m_blaster->getX(), 2));
	if( x < .75 * (getRadius() +m_blaster->getRadius())) {
		m_health = 0;
		m_blaster->collision();
		return 1;
	}
	list <Actors*> ::iterator it = m_acts.begin();
	while (it != m_acts.end()) {
		if((*it)->getType()==3){
			 x = sqrt(pow(getX() + (*it)->getX(), 2.0) + pow(getX() + (*it)->getX(), 2));
			if (x < .75 * (getRadius() + (*it)->getRadius())) {
				m_health -= 2;
				(*it)->collision();
				
				return 1;
			}
		}
		else { it++; }
		}
	if (m_pathLength == 0 || getY() >= VIEW_HEIGHT - 1 || getY() <= 0) {
		m_pathLength = randInt(1, 32);
		if (getY() >= VIEW_HEIGHT - 1)
			moveTo(getX() - m_speed, getY() - m_speed);
		else if (getY() <= 0)
			moveTo(getX() + m_speed, getY() + m_speed);
		else {
			int x = randInt(1, 3);
			if (x == 1)
				moveTo(getX() + m_speed, getY());
			else if (x == 2)
				moveTo(getX() + m_speed, getY() + m_speed);
			else moveTo(getX() - m_speed, getY() - m_speed);
		}
		m_pathLength--;
	}
	if (m_health <= 0)
		return 0;
	 x = sqrt(pow(getX() + m_blaster->getX(), 2.0) + pow(getX() + m_blaster->getX(), 2));
	if (x < .75 * (getRadius() + m_blaster->getRadius())) {
		m_health = 0;
		m_blaster->collision();
		return 1;
	}
    it = m_acts.begin();
	while (it != m_acts.end()) {
		if ((*it)->getType() == 3) {
			x = sqrt(pow(getX() + (*it)->getX(), 2.0) + pow(getX() + (*it)->getX(), 2));
			if (x < .75 * (getRadius() + (*it)->getRadius())) {
				m_health -= 2;
				(*it)->collision();

				return 1;
			}
		}
		else { it++; }
	}
	

	


}
bool Smallgon::isDead() { return true; }
Smallgon::~Smallgon(){}

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
