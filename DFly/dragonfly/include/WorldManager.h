///
/// The game world manager
///

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Box.h"
#include "Circle.h"
#include "Line.h"
#include "Manager.h"
#include "ObjectList.h"
#include "Vector.h"
#include "SceneGraph.h"

// Two-letter acronym for easier access to manager.
#define WM df::WorldManager::getInstance()

namespace df {

class WorldManager : public Manager {

 private:
  WorldManager();                 ///< Private since a singleton.
  WorldManager (WorldManager const&);  ///< Don't allow copy.
  void operator=(WorldManager const&); ///< Don't allow assignment.
  SceneGraph m_scene_graph;       ///< Storage for all Objects, game and view.
  ObjectList m_deletions;         ///< List of all Objects to delete.
  Object *m_p_view_following;     ///< Object view is following.
  Box m_boundary;                 ///< World boundary.
  Box m_view;			  ///< Player view of game world.
  Vector m_view_slack;	          ///< "Slack" for view following.

 public:
  /// Get the one and only instance of the WorldManager.
  static WorldManager &getInstance();
  
  /// Startup game world (initialize everything to empty).
  /// Return 0.
  int startUp();

  /// Shutdown game world (delete all game world Objects).
  void shutDown();

  /// Accept all user-defined events (returns true).
  /// Return false for other engine events.
  bool isValid(std::string event_type) const;

  /// Add Object to world.
  /// Return 0 if ok, else -1.
  int insertObject(Object *p_o);

  /// Remove Object from world.
  /// Return 0 if ok, else -1.
  int removeObject(Object *p_o);

  /// Return list of all Objects in world.
  /// If inactive is true, include inactive Objects.
  ObjectList getAllObjects(bool inactive=false) const;

  /// Indicate Object is to be deleted at end of current game loop.
  /// Return 0 if ok, else -1.
  int markForDelete(Object *p_o);

  /// Indicate Objects in list are to be deleted at end of current game loop.
  /// Return 0 if ok, else -1.
  int markForDelete(ObjectList obj_list);

  /// Update world.
  /// Update positions of Objects based on their velocities.
  /// Lastly, delete Objects marked for deletion.
  void update();

  /// Draw all Objects in view.
  /// Draw bottom up, from 0 to MAX_ALTITUDE.
  void draw();

  /// Move Object. 
  /// If collision with solid, send collision events.
  /// If no collision with solid, move ok else don't move Object.
  /// If Object is Spectral, move ok.
  /// If move ok, adjust view if following this Object.
  /// If moved from inside world boundary to outside, generate EventOut.
  /// Return 0 if move ok, else -1 if collision with solid.
  int moveObject(Object *p_o, Vector where);

  /// Return list of Objects collided with at position 'where'.
  /// Collisions only with solid Objects.
  /// Does not consider if p_o is solid or not.
  ObjectList isCollision(const Object *p_o, Vector where) const;

  /// Return Object with indicated id.
  /// NULL if Object is not found.
  Object *objectWithId(int id) const;

  /// Return list of Objects matching type.
  /// List is empty if none found.
  ObjectList objectsOfType(std::string type) const;

  /// Return list of all Objects at position 'where'.  
  /// Does include bounding boxes. Return empty list if none found.
  ObjectList objectsAtPosition(Vector where) const;

  /// Return list of all Objects in Box.
  /// Does include bounding boxes. Return empty list if none found.
  ObjectList objectsInBox(Box box) const;

  /// Return a list of all Objects on line from point1 to point2.
  /// Does include bounding boxes. Return empty list if none found.
  ObjectList objectsOnLine(Line line) const;

  /// Return a list of all Objects in circle.
  /// Does include bounding boxes. Return empty list if none found.
  ObjectList objectsInCircle(Circle circle) const;

  /// Get game world boundary.
  Box getBoundary() const;

  /// Set game world boundary.
  void setBoundary(Box new_boundary);

  /// Get player view of game world.
  Box getView() const;

  /// Set player view of game world.
  void setView(Box new_view);

  /// Get player "slack" for view following.
  Vector getViewSlack() const;

  /// Set player "slack" for view following.
  void setViewSlack(Vector new_slack);

  /// Set view to center screen on Object.
  /// Set to NULL to stop following.
  /// If Object not legit, return -1 else return 0.
  int setViewFollowing(Object *p_new_view_following);

  /// Get Object view is following (NULL if none).
  Object *getViewFollowing() const;

  /// Set view to center screen on position view_pos.
  /// View edge will not go beyond world boundary.
  void setViewPosition(Vector view_pos);

  /// Return reference to SceneGraph.
  SceneGraph &getSceneGraph() const;
};

} // end of namespace df
#endif // __WORLD_MANAGER_H__
