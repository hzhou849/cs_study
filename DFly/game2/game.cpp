//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "Saucer.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);
 
int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();

  // Run game (this blocks until game loop is over).
  GM.run();
  
  // Shut everything down.
  GM.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {
  RM.loadSprite("sprites/saucer-spr.txt", "saucer");
}

// Populate world with some objects.
void populateWorld(void) {
  new Saucer;
}
