//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "Saucer.h"

//Load Saucer sprites
void loadResources(void) {
	RM.loadSprite("sprites/saucer-spr.txt", "saucer");
}

void populateWorld(void) {
	new Saucer();
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Show splash screen.
  df::splash();

  //Load gaem resources
  loadResources();

  //Populate game world with some objects
  populateWorld();
  GM.run();

  // Shut everything down.
  game_manager.shutDown();
}
