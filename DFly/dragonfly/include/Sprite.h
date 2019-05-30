///
/// The sprite
/// 

#ifndef __SPRITE_H__
#define __SPRITE_H__

// System includes.
#include <string>

// Engine includes.
#include "Color.h"
#include "Frame.h"

namespace df {

class Sprite {

 private:
  int m_width;            ///< Sprite width.
  int m_height;           ///< Sprite height.
  int m_max_frame_count;  ///< Maximum number of frames sprite can have.
  int m_frame_count;      ///< Actual number of frames sprite has.
  Color m_color;	  ///< Optional color for entire sprite.
  Frame *m_frame;         ///< Array of frames.
  std::string m_label;	  ///< Text label to identify sprite.
  Sprite();               ///< Sprite constructor always has one arg.

 public:
  /// Delete sprite, removing any allocated frames.
  ~Sprite();

  /// Create sprite with indicated maximum number of frames.
  Sprite(int max_frames);  

  /// Set width of sprite.
  void setWidth(int new_width);

  /// Get width of sprite.
  int getWidth() const;

  /// Set height of sprite.
  void setHeight(int new_height);

  /// Get height of sprite.
  int getHeight() const;

  /// Set sprite color.
  void setColor(Color new_color);

  /// Get sprite color.
  Color getColor() const;

  /// Get total count of frames in sprite.
  int getFrameCount() const;

  /// Add frame to sprite.
  /// Return -1 if frame array full, else 0.
  int addFrame(Frame new_frame);

  /// Get next sprite frame indicated by number.
  /// Return empty frame if out of range [0, frame_count].
  Frame getFrame(int frame_number) const;

  /// Set label associated with sprite.
  void setLabel(std::string new_label);

  /// Get label associated with sprite.
  std::string getLabel() const;
};

} // end of namespace df
#endif // __SPRITE_H__
