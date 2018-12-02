///
/// A basic button
///
/// Invokes callback() when clicked.
/// Changes to highlight color on mouse over.
/// 

#ifndef __BUTTON_H__
#define __BUTTON_H__

// Engine includes.
#include "EventMouse.h"    
#include "ViewObject.h"

namespace df {

/// Count of number of button modified attribute categories.
const int BATTR_COUNT = 2;

/// Categories of button attributes that indicate modification.
enum ButtonAttribute {
  HIGHLIGHT_COLOR,
  DEFAULT_COLOR,
};

class Button : public ViewObject {

 private:
  Color m_highlight_color;	 ///< Color when highlighted.
  Color m_default_color;	 ///< Color when not highlighted.
  bool m_bmodified[BATTR_COUNT]; ///< Modified attribute since serialize().

 public:
  Button();

  /// Handle "mouse" events.
  /// Return 0 if ignored, else 1.
  int eventHandler(const Event *p_e);

  /// Set highlight (when mouse over) color for Button.
  void setHighlightColor(Color new_highlight_color);

  /// Get highlight (when mouse over) color for Button.
  Color getHighlightColor() const;

  /// Set color of Button.
  void setDefaultColor(Color new_default_color);

  /// Get color of Button
  Color getDefaultColor() const;

  /// Return true if mouse over Button, else false. 
  bool mouseOverButton(const EventMouse *p_e) const;

  /// Called when Button clicked.
  /// Must be defined by derived class.
  virtual void callback() = 0;

  /// Serialize Button attributes to single string.
  /// Only modified attributes (unless all is true).
  virtual std::string serialize(bool all = false);

  /// Deserialize string to become attributes.
  /// Rerturn 0 if no errors, else -1.  
  virtual int deserialize(std::string s);

  /// Return true if attribute modified since last serialize.
  virtual bool isModified(enum ButtonAttribute attribute) const;
  
  /// Return true if any attribute modified since last serialize.
  virtual bool isModified() const;
};

} // end of namespace df
#endif
