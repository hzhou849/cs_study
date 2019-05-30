///
/// The base game world object
///

#ifndef __OBJECT_H__
#define __OBJECT_H__

// System includes.
#include <string>

// Engine includes.
#include "Box.h"              ///< Objects have a bounding box.
#include "Event.h"            ///< Objects can handle events.
#include "Path.h"	      ///< Objects can seek along path.
#include "PathFind.h"	      ///< Objects can do pathfinding.
#include "Shape.h"	      ///< Objects can have simple drawing shapes.
#include "Sprite.h"           ///< Objects (often) have sprites.
#include "Vector.h"           ///< Objects need a float location.

namespace df {

/// Max number of events Object can be interested in.
const int MAX_OBJ_EVENTS = 100;

/// Types of solidness of Object.
enum Solidness {
  HARD,       ///< Object causes collisions and impedes.
  SOFT,       ///< Object causes collision, but doesn't impede.
  SPECTRAL,   ///< Object doesn't cause collisions.
};
 
/// Count of number of modified attribute categories.
const int ATTR_COUNT = 18;

/// Categories of attributes that indicate modification.
enum ObjectAttribute {
  ID, 
  ACTIVE,
  VISIBLE,            
  EVENTS,
  BOX,                   
  POSITION,               
  TYPE,                
  SPRITE,
  ALTITUDE,               
  SOLIDNESS,        
  NO_SOFT,               
  SPEED,
  DIRECTION,
  ACCELERATION,
  SHAPE,
  PATH,
  FOLLOW_PATH,
  AVOID_COLLISIONS,
};

class PathFind;  // Forward reference.

class Object {

 private:
  int m_id;		        ///< Unique game engine defined identifier.
  std::string m_type;	        ///< Game-programmer defined identification.
  bool m_is_active;             ///< If false, Object not acted upon.
  bool m_is_visible;            ///< If true, Object gets drawn.
  Box m_box;                    ///< Box for sprite boundary & collisions.
  Vector m_position;            ///< Position in game world.
  Vector m_direction;	        ///< Direction vector.
  float m_speed;                ///< Object speed in direction.
  Vector m_acceleration;	///< Acceleration vector.
  std::string sprite_name;      ///< Sprite name in ResourceManager.
  Sprite *m_p_sprite;           ///< Sprite associated with Object.
  bool m_sprite_center;         ///< True if sprite centered on position.
  char m_sprite_transparency;   ///< Sprite transparent character (0 if none).
  int m_sprite_index;           ///< Current index frame for sprite.
  int m_sprite_slowdown;        ///< Slowdown rate (1 = no slowdown, 0 = stop).
  int m_sprite_slowdown_count;  ///< Slowdown counter.
  int m_altitude;               ///< 0 to MAX_ALTITUDE (higher drawn on top).
  Solidness m_solidness;        ///< Solidness state of Object.
  bool m_no_soft;               ///< True if won't move on SOFT Objects.
  int m_event_count;            ///< Number of events of interest.
  std::string m_event_name[MAX_OBJ_EVENTS]; ///< Names of events interested in.
  bool m_modified[ATTR_COUNT];  ///< Mod. attrib. since last serialize().
  Shape m_shape;	        ///< Basic geometric shape to draw.
  PathFind *m_p_path_find;      ///< Object performing pathfinding.
  Path m_path;                  ///< If following path, holds path information.
  bool m_follow_path;           ///< True if following path.
  bool m_avoid_collisions;      ///< True if should avoid collisions with HARD.

 public:

  /// Construct Object. 
  /// Set default parameters and add to game world (WorldManager).
  Object();

  /// Destroy Object. 
  /// Unregister for any interested events.
  /// Remove from game world (WorldManager).
  virtual ~Object();

  /// Set Object id.
  void setId(int new_id);

  /// Get Object id.
  int getId() const;
  
  /// Set type identifier of Object.
  void setType(std::string new_type);

  /// Get type identifier of Object.
  std::string getType() const;

  /// Set position of Object.
  virtual void setPosition(Vector new_position);

  /// Get position of Object.
  Vector getPosition() const;

  /// Handle event (default only handles pathfinding).
  /// Return 0 if ignored, else 1.
  virtual int eventHandler(const Event *p_event);

  /// Return True if Object is HARD or SOFT, else false.
  bool isSolid() const;    

  /// Set solidness of Object, with checks for consistency.  
  /// Return 0 if ok, else -1.
  int setSolidness(Solidness new_solid);

  /// Return solidness of Object.
  Solidness getSolidness() const;

  /// Set "no soft" setting of Object (true - cannot move onto SOFT Objects).
  void setNoSoft(bool new_no_soft=true);

  /// Get "no soft" setting of Object (true - cannot move onto SOFT Objects).
  bool getNoSoft() const;

  /// Set "avoid collisions" (true - avoid collisions with HARD when moving).
  void setAvoidCollisions(bool new_avoid_collisions=true);

  /// Get "avoid collisions" (true - avoid collisions with HARD when moving).
  bool getAvoidCollisions() const;

  /// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
  /// Return 0 if ok, else -1.
  int setAltitude(int new_altitude);
   
  /// Return altitude of Object.
  int getAltitude() const;
   
  /// Set speed of Object.
  void setSpeed(float speed);

  /// Get speed of Object.
  float getSpeed() const;

  /// Set direction of Object.
  void setDirection(Vector new_direction);

  /// Get direction of Object.
  Vector getDirection() const;

  /// Set direction and speed of Object.
  void setVelocity(Vector velocity);

  /// Get velocity of Object based on direction and speed.
  Vector getVelocity() const;

  /// Set acceleration of Object.
  void setAcceleration(Vector new_acceleration);

  /// Get acceleration of Object.
  Vector getAcceleration() const;

  /// Add acceleration to Object velocity.
  /// (Typically done once per step by World Manager).
  void accelerate();

  /// Predict Object position based on speed and direction.
  /// Return predicted position.
  Vector predictPosition();

  /// Navigate Object from current position to target position
  /// using pathfinding.
  /// Turns on avoid collisions.
  void pathTo(Vector position);

  /// Navigate Object from current position to current position
  /// of target Object using pathfinding.
  /// Turns on avoid collisions.
  void pathTo(Object *p_o_target);

  /// Set direction of Object towards position.
  /// (Called when pathfinding).
  void moveTo(Vector position);

  /// If following a path, update path progress.
  void doPathFollowing();

  /// Set visibility of Object.  Objects not visible are not drawn.
  /// Return 0 if ok, else -1.
  int setVisible(bool visible=true);

  /// Return visibility of Object.  Objects not visible are not drawn.
  bool isVisible() const;

  /// Set activeness of Object.  Objects not active are not acted upon
  /// by engine.
  /// Return 0 if ok, else -1.
  int setActive(bool active=true);

  /// Return activeness of Object.  Objects not active are not acted upon
  /// by engine.
  bool isActive() const;

  /// Set bounding box of Object.
  void setBox(Box new_box);

  /// Get bounding box of Object.
  Box getBox() const;

  /// Register for interest in event.  
  /// Keeps track of manager and event.  
  /// Return 0 if ok, else -1.
  int registerInterest(std::string event_type);

  /// Unregister for interest in event.  
  /// Return 0 if ok, else -1.
  int unregisterInterest(std::string event_type);

  /// Draw single Sprite Frame.
  /// Drawing accounts for centering & slowdown, and advances Sprite Frame.
  virtual void draw();

  /// Set Sprite name (in ResourceManager) for Object.
  void setSpriteName(std::string new_name);

  /// Get Sprite name (in ResourceManager) for Object.
  std::string getSpriteName() const;

  /// Set Object Sprite to new one.
  /// If set_box is true, set bounding box to size of Sprite.
  /// Set sprite index to 0 (first frame).
  void setSprite(Sprite *p_new_sprite, bool set_box=true);

  /// Return pointer to Sprite associated with this Object.
  Sprite *getSprite() const;

  /// Set Sprite to be centered at Object position.
  /// Adjust bounding box of Sprite.
  void setCentered(bool centered=true);

  /// Indicates if Sprite is centered at Object position.
  bool isCentered() const;

  /// Set Sprite transparency character (0 means none).
  void setTransparency(char transparent=' ');

  /// Get Sprite transparency character (0 means none).
  char getTransparency() const;

  /// Set index of current Sprite frame to be displayed.
  void setSpriteIndex(int new_sprite_index);

  /// Return index of current Sprite frame to be displayed.
  int getSpriteIndex() const;

  /// Slows down sprite animations.
  /// Slowdown value in multiples of GameManager frame time.
  void setSpriteSlowdown(int new_sprite_slowdown);
  int getSpriteSlowdown() const;
  void setSpriteSlowdownCount(int new_sprite_slowdown_count);
  int getSpriteSlowdownCount() const;
  
  /// Serialize attributes to single string.
  /// e.g., "id:110,is_active:true, ...
  /// Only modified attributes are serialized (unless all is true).
  /// Clear modified[] array.
  virtual std::string serialize(bool all=false);

  /// Deserialize string to become attributes.
  /// Return 0 if no errors, else -1.  
  virtual int deserialize(std::string s);

  /// Return true if attribute modified since last serialize.
  virtual bool isModified(enum ObjectAttribute attribute) const;
  
  /// Return true if any attribute modified since last serialize.
  virtual bool isModified() const;

  /// Set drawing shape.
  void setShape(Shape new_shape);

  /// Get drawing shape.
  Shape getShape() const;

  /// Set follow_path (note: is also set in pathTo() method).
  /// If path defined, start moving to first node.
  void setFollowPath(bool new_follow_path=true);

  /// Returns true if following a path (note: is set in pathTo() method).
  bool getFollowPath() const;

  /// Set Path (note: is also set in pathTo() method).
  void setPath(Path new_path);

  /// Get Path (note: is set in pathTo() method).
  Path getPath() const;

  /// Get object doing pathfinding. 
  PathFind *getPathFind();
};

} // end of namespace df
#endif // __OBJECT_H__
