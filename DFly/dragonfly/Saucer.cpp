

// Engine includes
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

// Game includes
#include "Saucer.h"

Saucer::Saucer() {
	//Setup "saucer" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("saucer");
	if (!p_temp_sprite)
		LM.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found", "saucer");
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}

	//Set object type
	setType("Saucer");

	//Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25,0)); // 1 space every 4 frames

	//set Starting location in the middle of window.
	int world_horiz = (int) WM.getBoundary().getHorizontal();
	int world_vert = (int) WM.getBoundary().getVertical();
	df::Vector p(world_horiz/2, world_vert/2);
	setPosition(p);
}

int Saucer::eventHandler(cosnt df::Event *p_e) {
    if (p_e->getType() == df::OUT_EVENT) {  // if out event occurs , the saucer out method is called.
        out();
        return 1;
    }
    return 0;

}

void Saucer::out() {
// If moved off left edge, move back to rigth
if (getPosition().getX() >= 0)  // if greater than 0, the saucer did not go out of bounds
    return;
}

void Saucer::moveToStart() {
    df::Vector
}