///
/// A precipitation particle
///

#ifndef __PRECIPITATION_H__
#define __PRECIPITATION_H__

// Engine include.
#include "Particle.h"

namespace df {

/// Precipitation types.
enum PrecipitationType {
  UNDEFINED_PRECIPITATION_TYPE = -1,
  SNOW,
  RAIN,
  STARFIELD,
};

class Precipitation : public Particle {

 private:
  Direction m_direction;	 ///< Direction precipitation travelling.
  Vector m_velocity_init;	 ///< Initial velocity.
  bool m_turbulence;             ///< True if turbulence.

 public:
  
  /// Constructor, specifing size, direction, opacity and rgb.
  Precipitation(float size, Direction direction, unsigned char opacity,
	   unsigned char r, unsigned char g, unsigned char b);

  /// Handle step events.
  /// Return 0 if ignored, else 1.
  int eventHandler(const Event *p_e);

  /// Set turbulence of Precipitation.
  void setTurbulence(bool new_turbulence = true);
};

} // end of namespace df

#endif //__PRECIPITATION_H__
