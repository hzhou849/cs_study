///
/// Text for splash screen
/// 

#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "EventStep.h"
#include "Object.h"	

namespace df {

class Splash : public Object {

 private:
  int m_countdown;  /// Countdown to event actions.

 public:
  Splash();
  ~Splash();
  int eventHandler(const Event *p_e);
};
 
} // end of namespace df
#endif // __SPLASH_H__
