
#include "entity.h"
#include <vector.h>

class Game{
  private:
	std::vector<Entity> entityTemplates;
	std::vector<Entity> entities;
	int state;
  public:
	Game();
	void update(int t, int dt);
	
	bool addEntity(Entity);
	bool removeEntityByID(ID);
	
	int getState(){return state};
	void reset();
	void start();
}
