//
// Saucer.cpp
//
 
// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventOut.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Saucer.h"

Saucer::Saucer() {

  // Setup "saucer" sprite.
  df::Sprite *p_temp_sprite = RM.getSprite("saucer");
  if (!p_temp_sprite)
    LM.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found", "saucer");
  else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(4);		
  }

  // Set object type.
  setType("Saucer");

  // Set speed in horizontal direction.
  setVelocity(df::Vector(-0.25,0)); // 1 space left every 4 frames

  // Move Saucer to start location.
  moveToStart();
}

// Handle event.
// Return 0 if ignored, else 1.
int Saucer::eventHandler(const df::Event *p_e) {
 
  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }
  // If get here, have ignored this event.
  return 0;
}
 
// If moved off left edge, move back to far right.
void Saucer::out() {
 
  // If haven't moved off left edge, then nothing to do.
  if (getPosition().getX() >= 0)
    return;
 
  // Otherwise, move back to far right.
  moveToStart();
 
}
 
// Move Saucer to starting location on right side of window.
void Saucer::moveToStart() {
  df::Vector temp_pos;

  // Get world boundaries.
  int world_horiz = (int) WM.getBoundary().getHorizontal();
  int world_vert = (int) WM.getBoundary().getVertical();

  // x is off right side of window.
  temp_pos.setX(world_horiz + rand()%(int)world_horiz + 3.0f);

  // y is in vertical range.
  temp_pos.setY(rand()%(int)(world_vert-1) + 1.0f);

  WM.moveObject(this, temp_pos);
}
