/// 
/// PathManager.h
/// 
/// Manage pathfinding for all Objects.
/// 

#ifndef __PATH_MANAGER_H__
#define __PATH_MANAGER_H__

// System includes.
#include <string>
#include <vector>

// Engine includes.
#include "Manager.h"
#include "PathFind.h"

// Two-letter acronym for easier access to manager.
#define PM df::PathManager::getInstance()

namespace df {

class PathManager : public Manager {

 private:
  PathManager();		      ///< Private since a singleton.
  PathManager(PathManager const&);    ///< Don't allow copy.
  void operator=(PathManager const&); ///< Don't allow assignment.
  std::vector<PathFind *> m_finder;   ///< PathFind's registered.
  int m_min_cycle_time;	              ///< Min pathfinding time, in millisec.
  
 public:

  /// Get the one and only instance of the PathManager.
  static PathManager &getInstance();

  /// Start up PathManager.
  /// Set min cycle time default to 1/10 frame time.
  int startUp();

  /// Shut down PathManager.
  void shutDown();

  /// Register PathFind with PathManager.
  /// Return 0 if ok, else -1.
  int registerPathFind(PathFind *p_path_find);

  /// Unregister PathFind with PathManager.
  /// Return 0 if ok, else -1.
  int unregisterPathFind(PathFind *p_path_find);

  /// Set minimum cycle time (minimum game loop time spent pathfinding).
  void setMinCycleTime(int new_min_cycle_time);

  /// Get minimum cycle time (minimum game loop time spent pathfinding).
  int getMinCycleTime();

  /// Cycle through registered PathFinders.
  /// Spend at least min_cycle time, but no more than max_cycle_time.
  void cycle(int max_cycle_time=-1);
};

} // end of namespace df

#endif // __PATH_MANAGER_H__
