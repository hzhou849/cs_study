//
// An path class.
//

#ifndef __PATH_H__
#define __PATH_H__

// System includes.
#include <vector>

// Engine includes.
#include "Vector.h"

namespace df {

class Path {

 private:
  std::vector<Vector> m_path;	///< Nodes in path.
  int m_index;		        ///< Index of next target node.

 public:
  Path();

  /// Return next node in path.
  /// Return (-1,-1) if none.
  Vector nextNode() const;

  /// Return previous node in path.
  /// Return (-1,-1) if none.
  Vector previousNode() const;

  /// Set path.
  void setPath(std::vector<Vector> new_path);

  /// Return path.
  std::vector<Vector> getPath() const;

  /// Return true when at end of path.
  bool endOfPath() const;

  /// Return last node of path.
  Vector getEnd() const;

  /// Set index of path.
  /// Return 0 if ok, else -1;
  int setIndex(int new_index);

  /// Return index of path.
  int getIndex() const;

  /// Increment path target node.
  /// If at last node, index stays at end.
  Path operator++(int);
};

} // end of namespace df
#endif //__PATH_H__
