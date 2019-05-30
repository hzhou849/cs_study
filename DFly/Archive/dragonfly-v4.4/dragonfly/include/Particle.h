///
/// A particle
///

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// Engine include.
#include "Object.h"

namespace df {

/// Constants.
const int NO_SPREAD=0;  // Particles spread.

/// Particle types.
enum ParticleType {
  UNDEFINED_PARTICLE_TYPE = -1,
  SMOKE,
  SPARKS,
  RINGS,
  FIREWORKS,
};

/// Particle classes.
enum ParticleClass {
  UNDEFINED_PARTICLE_CLASS = -1,
  PARTICLE,
  FIREWORK,
};

/// Directions.
enum Direction {
  UNDEFINED_DIRECTION = -1,
  UP,
  DOWN,
  LEFT, 
  RIGHT,
};

class Particle : public Object {

 private:
  int m_age;			///< Age to live (in ticks).

 public:
  /// Create particle with size (pixels), age (in ticks), opacity
  /// (0-255) and rgb color.
  Particle(float size, int age, unsigned char opacity, 
	   unsigned char r, unsigned char g, unsigned char b);

  /// Set age.
  void setAge(int new_age);

  /// Get age.
  int getAge() const;

  /// Handle step events.
  /// Return 0 if ignored, else 1.
  int eventHandler(const Event *p_e);
};

} // end of namespace df
#endif //__PARTICLE_H__
