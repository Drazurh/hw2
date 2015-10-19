#define MAX_ENT = 200;

#include "entity.h"

class State{
  private:
	Entity entities[MAX_ENT];
	int num_entities;
	int state;
	
  public:
	void update(int t, int dt);
	
	bool addEntity(Entity);
	bool removeEntityByID(ID);
	
	int getState(){return state};
	void reset();
	void start();
}