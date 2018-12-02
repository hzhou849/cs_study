///
/// A line segment
///

#ifndef __LINE_H__
#define __LINE_H__

#include "Vector.h"

namespace df {

class Line {

 private:
  Vector m_p1;            ///< First endpoint.
  Vector m_p2;            ///< Second endpoint.

 public:

  /// Create line segment from p1 to p2.
  Line(Vector init_p1, Vector init_p2);

  /// Default line segment is at (0,0).
  Line();

  void setP1(Vector new_p1);  ///< Set first endpoint.
  Vector getP1() const;       ///< Get first endpoint.
  void setP2(Vector new_p2);  ///< Set second endpoint.
  Vector getP2() const;       ///< Get second endpoint.
};

} // end of namespace df
#endif //__LINE_H__
