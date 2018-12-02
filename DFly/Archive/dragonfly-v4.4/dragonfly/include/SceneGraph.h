///
/// A scene graph
///

#ifndef __SCENE_GRAPH_H__
#define __SCENE_GRAPH_H__

#include "Object.h"
#include "ObjectList.h"

namespace df {

const int MAX_ALTITUDE = 4;

class SceneGraph {

 private:
  ObjectList m_active_objects;   ///< All active Objects.
  ObjectList m_solid_objects;    ///< Solid Objects.
  ObjectList m_visible_objects[MAX_ALTITUDE+1]; ///< Visible Objects.
  ObjectList m_inactive_objects; ///< All inactive Objects.
  
 public:
  SceneGraph();
  
  /// Insert Object into SceneGraph.
  int insertObject(Object *p_o);

  /// Remove Object from SceneGraph.
  int removeObject(Object *p_o);

  /// Return all active Objects. Empty list if none.
  ObjectList activeObjects() const;

  /// Return all active, solid Objects. Empty list if none.
  ObjectList solidObjects() const;

  /// Return all active, visible Objects at altitude. Empty list if none.
  ObjectList visibleObjects(int altitude) const;

  /// Return all inactive Objects. Empty list if none.
  ObjectList inactiveObjects() const;
  
  /// Re-position Object in SceneGraph to new altitude.
  /// Return 0 if ok, else -1.
  int updateAltitude(Object *p_o, int new_alt);

  /// Re-position Object in SceneGraph to new solidness.
  /// Return 0 if ok, else -1.
  int updateSolidness(Object *p_o, Solidness new_solidness);

  /// Re-position Object in SceneGraph to new visibility.
  /// Return 0 if ok, else -1.
  int updateVisible(Object *p_vo, bool new_visible);

  /// Re-position Object in SceneGraph to new activeness.
  /// Return 0 if ok, else -1.
  int updateActive(Object *p_o, bool new_active);
};
  
} // end of namespace df
#endif // __SCENE_GRAPH_H__
