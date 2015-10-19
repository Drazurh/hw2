#include "entity.h"
#include <vector>

#ifndef Game_h
#define Game_h

class Game{
  private:
	std::vector<Entity> entityTemplates;
	std::vector<Entity> entities;
	int state;
  public:
	Game();
	bool addEntity(Entity);
	bool removeEntityByID(int);
	
	void update(int t, int dt);

	int getState(){return state;};
	void reset();
	void start();
};

#endif
