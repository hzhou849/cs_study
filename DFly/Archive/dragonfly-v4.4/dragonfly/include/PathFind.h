///
/// An A* pathfinding class.
///

#ifndef __PATHFIND_H__
#define __PATHFIND_H__

// Engine includes.
#include "EventPath.h"
#include "Object.h"
#include "Vector.h"

namespace df {

class Object;     // Forward reference.

// Coordinates for pathfinding.
struct coord_struct {
  int x, y;
};

// Nodes for pathfinding.
struct node_struct {
  float from_start; // Cost from start.
  float to_end;     // Estimate to end + cost from start.
  struct coord_struct came_from;  // Most efficient path back.
};

class PathFind {

 private:
  Object *m_p_o;	                 ///< Object finding path.
  Object *m_p_target_o;			 ///< Object target (optional).
  coord_struct m_start;			 ///< Start position.
  coord_struct m_end;			 ///< End target position.
  struct node_struct **m_node;           ///< Nodes in graph.
  std::vector<coord_struct> m_open_set;  ///< Set of nodes not yet visited.
  std::vector<coord_struct> m_closed_set;///< Set of nodes visited.
  int m_num_plies;		         ///< Number of plies cycled.
  bool m_is_path;			 ///< True if path is complete.

 public:

  /// Constructor needs Object doing pathfinding, start and end locations.
  PathFind(Object *p_o, Vector start, Vector end);
  ~PathFind();

  /// Go through one search cycle.  
  /// Returns indicatation if found path {found, not found, incomplete}.
  SearchResult cycleOnce();

  /// Return path.
  Path getPath() const;

  /// Set object seeking path.
  void setObject(Object *new_p_o);

  /// Return object seeking path.
  Object *getObject() const;

  /// Return number of plies.
  int getNumPlies() const;

  /// Set target object.
  /// Pathfinding stops when target object discovered.
  void setTargetObject(Object *p_target_o);

  /// Get target object.
  /// Pathfinding stops when target object discovered.
  Object *getTargetObject();
};

} // end of namespace df
#endif //__PATHFIND_H__
