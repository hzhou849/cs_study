
// Engine includes
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes
#include "Saucer.h"

Saucer::Saucer() {
	//Setup "saucer" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("saucer");
	if (!p_temp_spirte)
		LM.writelog("Saucer::Saucer(): Warning! Sprite '%s' not found", "saucer");
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