///
/// Fraps (FRAmes Per Second) recorder
/// 

#ifndef __FRAPS_H__
#define __FRAPS_H__

// System includes.
#include <stdio.h>
#include <SFML/Graphics.hpp>

// Engine includes.
#include "Clock.h"    
#include "Event.h"    
#include "ViewObject.h"

namespace df {

const std::string FRAPS_STRING = "fps";
const std::string FRAPS_FILENAME = "fraps";
#define FRAPS_LOG_MESSAGE "Fraps: frame rate %.0f f/s"

class Fraps : public ViewObject {

 private:
  bool m_do_record;         ///< True if recording.
  bool m_do_frame_rate;	    ///< True if logging frame rate.
  Clock m_clock;            ///< For computing frame rate.
  FILE *m_p_screen;	    ///< Output file handle.
  sf::Texture m_texture;    ///< Texture for image capture.

 public:
  /// Frames per second meter (with option to record screen).
  /// defaults: TOP_RIGHT, green, don't record, don't log frame rate.
  Fraps(bool do_record=false);
  ~Fraps();

  /// Handle event each step.
  /// Handle keyboard events:
  /// - f9 to show/hide
  /// - f11 to toggle logging frame rate
  /// - f12 to toggle recording
  int eventHandler(const Event *p_e);

  /// Set whether record or not.
  void setRecord(bool new_record);

  /// Set whether log frame rate or not.
  void setLogFrameRate(bool new_do_frame_rate);
};

} // end of namespace df
#endif
