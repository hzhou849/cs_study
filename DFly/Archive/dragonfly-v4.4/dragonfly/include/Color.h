///
/// Colors for Dragonfly
///

#ifndef __COLOR_H__
#define __COLOR_H__

namespace df {

/// Colors Dragonfly recognizes.
enum Color {
  UNDEFINED_COLOR = -1,
  BLACK = 0,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  CUSTOM,
};

/// If color not specified, will use this.
const Color COLOR_DEFAULT = WHITE;

} // end of namespace df
#endif //__COLOR_H__
