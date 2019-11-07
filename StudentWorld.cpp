#include "StudentWorld.h"
#include "GameConstants.h"

#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
}

int StudentWorld::init()
{
	m_nachy = new NachenBlaster(this);
	for (int i = 0; i < 30; i++)
		m_actors.push_front(new Star(randInt(0, VIEW_WIDTH - 1), randInt(0, VIEW_HEIGHT - 1)));
	m_eDefeated = 0;
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	int i=m_nachy->doSomething();
	if (i == 1)
		m_actors.push_back(new Cabbage(m_nachy));
	m_it = m_actors.begin();

	while (m_it != m_actors.end()) {
		(*m_it)->doSomething();
		if ((*m_it)->isDead()) {
			delete (*m_it);
			m_it = m_actors.erase(m_it);
		}
		else { m_it++; }
	}
	if (randInt(1, 15) == 15)
		m_actors.push_front(new Star(VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	delete m_nachy;
	while (!m_actors.empty()) {
		delete (*m_it);
		m_it = m_actors.erase(m_it);
	}
}
