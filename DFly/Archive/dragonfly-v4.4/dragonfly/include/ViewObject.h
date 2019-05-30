///
/// The view object
///

#ifndef __VIEW_OBJECT_H__
#define __VIEW_OBJECT_H__

// System includes.
#include <string>

// Engine includes.
#include "Color.h"
#include "Event.h"        
#include "Object.h"

namespace df {

/// Count of number of view object modified attribute categories.
const int VATTR_COUNT = 6;

/// Categories of view object attributes that indicate modification.
enum ViewObjectAttribute {
  VIEW_STRING,
  VALUE,
  BORDER,
  COLOR,
  LOCATION,
  DRAW_VALUE,
};

/// General location of ViewObject on screen.
enum ViewObjectLocation {
  UNDEFINED=-1,
  TOP_LEFT,
  TOP_CENTER,
  TOP_RIGHT,
  CENTER_LEFT,
  CENTER_CENTER,
  CENTER_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT,
};

class ViewObject : public Object {

 private:
  std::string m_view_string;     ///< Label for value (e.g., "Points").
  int m_value;                   ///< Value displayed (e.g., points).
  bool m_draw_value;	         ///< True if should draw value.
  bool m_border;                 ///< True if border around display.
  Color m_color;                 ///< Color for text (and border).
  ViewObjectLocation m_location; ///< Location of ViewObject.
  bool m_vmodified[VATTR_COUNT]; ///< Mod. attrib. since serialize().

 public:
  /// Construct ViewObject. 
  /// Object settings: SPECTRAL, max altitude.
  /// ViewObject defaults: border, top_center, default color, draw_value.
  ViewObject();

  /// Draw view string (and value).
  virtual void draw();

  /// Handle "view" event if tag matches view_string (others ignored).
  /// Return 0 if ignored, else 1.
  virtual int eventHandler(const Event *p_e);

  /// Set general location of ViewObject on screen.
  void setLocation(ViewObjectLocation new_location);

  /// Get general location of ViewObject on screen.
  ViewObjectLocation getLocation() const;

  /// Set true to draw value with display string.
  void setDrawValue(bool new_draw_value = true);

  /// Get draw value (true if draw value with display string).
  bool getDrawValue() const;

  /// Set view value.
  void setValue(int new_value);

  /// Get view value.
  int getValue() const;

  /// Set view border (true = display border).
  void setBorder(bool new_border);

  /// Get view border (true = display border).
  bool getBorder() const;

  /// Set view color.
  void setColor(Color new_color);

  /// Get view color.
  Color getColor() const;

  /// Set view display string.
  void setViewString(std::string new_view_string);

  /// Get view display string.
  std::string getViewString() const;
  
  /// Set position of ViewObject, with setting "location" to UNDEFINED.
  void setPosition(Vector new_pos);

  /// Serialize ViewObject attributes to single string.
  /// Only modified attributes (unless all is true).
  virtual std::string serialize(bool all = false);

  /// Deserialize string to become attributes.
  /// Rerturn 0 if no errors, else -1.  
  virtual int deserialize(std::string s);

  /// Return true if attribute modified since last serialize.
  virtual bool isModified(enum ViewObjectAttribute attribute) const;
  
  /// Return true if any attribute modified since last serialize.
  virtual bool isModified() const;
};

} // end of namespace df
#endif // __VIEW_OBJECT_H__
