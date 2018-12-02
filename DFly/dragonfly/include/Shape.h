///
/// A single-space, 2d shape for drawing.
///

#ifndef __SHAPE_H__
#define __SHAPE_H__

// System includes.
#include <SFML/Graphics/CircleShape.hpp>

// Engine includes.
#include "Color.h"
#include "Vector.h"

namespace df {

enum ShapeType {
  UNDEFINED_SHAPE = -1,
  CIRCLE,
  SQUARE,
  TRIANGLE,
};

class Shape {

 private:
  Color m_color;	      ///< Shape color.
  unsigned char m_r,m_g,m_b;  ///< RGB colors used if color is CUSTOM.
  ShapeType m_type;	      ///< Type of shape.
  float m_size;		      ///< Radius size (in pixels).
  unsigned char m_opacity;    ///< Opacity (transparent) 0 to 255 (opaque).

 public:

  /// Default is Circle, df::WHITE, size 1 character.
  Shape();

  /// Set size (in pixels).
  void setSize(float new_size);

  /// Get size (in pixels).
  float getSize() const;

  /// Set  type. 
  void setType(ShapeType new_type);

  /// Get type. 
  ShapeType getType() const;

  /// Set color, where input is Dragonfly Color.
  void setColor(Color new_color);

  /// Set color, where input is RGB.
  void setColor(unsigned char r, unsigned char g, unsigned char b);

  /// Get color.  Returns Dragonfly Color.
  Color getColor() const;

  /// Set opacity (0 is transparent, 255 is opaque).
  void setOpacity(unsigned char new_opacity);
  
  /// Get opacity (0 is transparent, 255 is opaque).
  unsigned char getOpacity() const;

  /// Draw self at given world position.
  void draw(Vector world_pos);
};

} // end of namespace df
#endif //__SHAPE_H__
